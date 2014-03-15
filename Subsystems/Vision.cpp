// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Vision.h"
#include "../Robotmap.h"
#include "../Commands/CheckHot.h"
#include "Vision/RGBImage.h"
#include "Vision/BinaryImage.h"
#include "Math.h"
#include <cmath>
const bool WRITE_IMAGES_TO_FILE = false;
Vision::Vision() : Subsystem("Vision") {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	hot = false;
	setupNetTable();

	
	//m_camera = AxisCamera::GetInstance();
	//this.m_camera = AxisCamera::GetInstance();
}
    
void Vision::InitDefaultCommand() {
	m_camera = &AxisCamera::GetInstance();
	m_camera->WriteCompression(50);
	m_camera->WriteResolution(AxisCamera::kResolution_320x240);
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DEFAULT_COMMAND
}
// Put methods for controlling this subsystem
// here. Call these from Commands.
void Vision::setupNetTable()
{
	//65,145,10,249,15,235
	Robot::netTable->PutNumber("RedLow", 200); 
	Robot::netTable->PutNumber("RedHigh", 255); 
	Robot::netTable->PutNumber("GreenLow", 200); 
	Robot::netTable->PutNumber("GreenHigh", 255); 
	Robot::netTable->PutNumber("BlueLow", 200); 
	Robot::netTable->PutNumber("BlueHigh", 255); 
}
bool Vision::isHot()
{
	return hot;
}
void Vision::fetchImage()
{
	if (m_camera->IsFreshImage())
	{
		image = m_camera->GetImage();
		if(WRITE_IMAGES_TO_FILE)
		{
			image->Write("1_InitialImage.bmp");
		}
		filterImage();
	}
}
void Vision::filterImage()
{
	//Get the filter values from the net table
	int RedLow = (int)(Robot::netTable->GetNumber("RedLow", 200));
	int RedHigh = (int)(Robot::netTable->GetNumber("RedHigh", 255)); 
	int GreenLow = (int)(Robot::netTable->GetNumber("GreenLow", 200)); 
	int GreenHigh = (int)(Robot::netTable->GetNumber("GreenHigh", 255)); 
	int BlueLow = (int)(Robot::netTable->GetNumber("BlueLow", 200)); 
	int BlueHigh = (int)(Robot::netTable->GetNumber("BlueHigh", 255)); 
	//Apply the RGB filter
	thresholdImage = image->ThresholdRGB(RedLow, RedHigh, GreenLow, GreenHigh, BlueLow, BlueHigh);
	if(WRITE_IMAGES_TO_FILE)
	{
		thresholdImage->Write("2_RGBFiltered.bmp");
	}
	//Remove small particles	
	ParticleFilterCriteria2 criteria[] = {
			{IMAQ_MT_AREA, AREA_MINIMUM, 65535, false, false}
	};	
	filteredImage = thresholdImage->ParticleFilter(criteria, 1);
	if(WRITE_IMAGES_TO_FILE)
	{
		thresholdImage->Write("3_ParticleFiltered.bmp");
	}
	processImage();
}
double computeDistance (BinaryImage *image, ParticleAnalysisReport *report) {
	double rectLong, height;
	int targetHeight;
	
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
	//using the smaller of the estimated rectangle long side and the bounding rectangle height results in better performance
	//on skewed rectangles
	height = min((double)report->boundingRect.height, rectLong);
	targetHeight = 32;
	
	return Y_IMAGE_RES * targetHeight / (height * 12 * 2 * tan(VIEW_ANGLE*PI/(180*2)));
}
double scoreRectangularity(ParticleAnalysisReport *report){
	if(report->boundingRect.width*report->boundingRect.height !=0){
		return 100*report->particleArea/(report->boundingRect.width*report->boundingRect.height);
	} else {
		return 0;
	}	
}
double ratioToScore(double ratio)
{
	return (max(0.0, min(100*(1-fabs(1-ratio)), 100.0)));
}
bool Vision::scoreCompare(Scores scores, bool vertical)
{
	bool isTarget = true;
	isTarget &= scores.rectangularity > RECTANGULARITY_LIMIT;
	if(vertical){
		isTarget &= scores.aspectRatioVertical > ASPECT_RATIO_LIMIT;
	} else {
		isTarget &= scores.aspectRatioHorizontal > ASPECT_RATIO_LIMIT;
	}
	return isTarget;
}
double scoreAspectRatio(BinaryImage *image, ParticleAnalysisReport *report, bool vertical){
	double rectLong, rectShort, idealAspectRatio, aspectRatio;
	idealAspectRatio = vertical ? (4.0/32) : (23.5/4);	//Vertical reflector 4" wide x 32" tall, horizontal 23.5" wide x 4" tall
	
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &rectLong);
	imaqMeasureParticle(image->GetImaqImage(), report->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &rectShort);
	
	//Divide width by height to measure aspect ratio
	if(report->boundingRect.width > report->boundingRect.height){
		//particle is wider than it is tall, divide long by short
		aspectRatio = ratioToScore(((rectLong/rectShort)/idealAspectRatio));
	} else {
		//particle is taller than it is wide, divide short by long
		aspectRatio = ratioToScore(((rectShort/rectLong)/idealAspectRatio));
	}
	return aspectRatio;		//force to be in range 0-100
}
void Vision::processImage()
{
	reports = filteredImage->GetOrderedParticleAnalysisReports();
	verticalTargetCount = horizontalTargetCount = 0;
	if(reports->size() > 0)
	{
//			printf("Report\n");
		scores = new Scores[reports->size()];
		for (unsigned int i = 0; i < MAX_PARTICLES && i < reports->size(); i++) {
			ParticleAnalysisReport *report = &(reports->at(i));
			
			//Score each particle on rectangularity and aspect ratio
			scores[i].rectangularity = scoreRectangularity(report);
			scores[i].aspectRatioVertical = scoreAspectRatio(filteredImage, report, true);
			scores[i].aspectRatioHorizontal = scoreAspectRatio(filteredImage, report, false);			
			
			//Check if the particle is a horizontal target, if not, check if it's a vertical target
			if(scoreCompare(scores[i], false))
			{
//					printf("particle: %d  is a Horizontal Target centerX: %d  centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
				horizontalTargets[horizontalTargetCount++] = i; //Add particle to target array and increment count
			} else if (scoreCompare(scores[i], true)) {
//					printf("particle: %d  is a Vertical Target centerX: %d  centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
				verticalTargets[verticalTargetCount++] = i;  //Add particle to target array and increment count
			} else {
//					printf("particle: %d  is not a Target centerX: %d  centerY: %d \n", i, report->center_mass_x, report->center_mass_y);
			}
//				printf("Scores rect: %f \nARvert: %f \n", scores[i].rectangularity, scores[i].aspectRatioVertical);
			
			//printf("ARhoriz: %f  \n", scores[i].aspectRatioHorizontal);	
		}
		//Zero out scores and set verticalIndex to first target in case there are no horizontal targets
		target.totalScore = target.leftScore = target.rightScore = target.tapeWidthScore = target.verticalScore = 0;
		target.verticalIndex = verticalTargets[0];
		for (int i = 0; i < verticalTargetCount; i++)
		{
			ParticleAnalysisReport *verticalReport = &(reports->at(verticalTargets[i]));
			for (int j = 0; j < horizontalTargetCount; j++)
			{
				ParticleAnalysisReport *horizontalReport = &(reports->at(horizontalTargets[j]));
				double horizWidth, horizHeight, vertWidth, leftScore, rightScore, tapeWidthScore, verticalScore, total;
				//Measure equivalent rectangle sides for use in score calculation
				imaqMeasureParticle(filteredImage->GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_LONG_SIDE, &horizWidth);
				imaqMeasureParticle(filteredImage->GetImaqImage(), verticalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &vertWidth);
				imaqMeasureParticle(filteredImage->GetImaqImage(), horizontalReport->particleIndex, 0, IMAQ_MT_EQUIVALENT_RECT_SHORT_SIDE, &horizHeight);
				
				//Determine if the horizontal target is in the expected location to the left of the vertical target
				leftScore = ratioToScore(1.2*(verticalReport->boundingRect.left - horizontalReport->center_mass_x)/horizWidth);
				//Determine if the horizontal target is in the expected location to the right of the  vertical target
				rightScore = ratioToScore(1.2*(horizontalReport->center_mass_x - verticalReport->boundingRect.left - verticalReport->boundingRect.width)/horizWidth);
				//Determine if the width of the tape on the two targets appears to be the same
				tapeWidthScore = ratioToScore(vertWidth/horizHeight);
				//Determine if the vertical location of the horizontal target appears to be correct
				verticalScore = ratioToScore(1-(verticalReport->boundingRect.top - horizontalReport->center_mass_y)/(4*horizHeight));
				total = leftScore > rightScore ? leftScore:rightScore;
				total += tapeWidthScore + verticalScore;
				
				//If the target is the best detected so far store the information about it
				if(total > target.totalScore)
				{
					target.horizontalIndex = horizontalTargets[j];
					target.verticalIndex = verticalTargets[i];
					target.totalScore = total;
					target.leftScore = leftScore;
					target.rightScore = rightScore;
					target.tapeWidthScore = tapeWidthScore;
					target.verticalScore = verticalScore;
				}
			}
			//Determine if the best target is a Hot target
			target.Hot = checkTargetHot(target);
		}
		
		if(verticalTargetCount > 0)
		{
			//Information about the target is contained in the "target" structure
			//To get measurement information such as sizes or locations use the
			//horizontal or vertical index to get the particle report as shown below
			//ParticleAnalysisReport *distanceReport = &(reports->at(target.verticalIndex));
			//double distance = computeDistance(filteredImage, distanceReport);
			if(target.Hot)
			{
				this->hot = true;
				printf("Hot\n"); //printf("Hot target located \n");
//				printf("Distance: %f\n", distance*1.125); //added the *1.125 to make the distance correct, check with M1013
			} else {
				this->hot = false;
				printf("Not Hot\n"); //printf("No hot target present \n");
//				printf("Distance: %f \n", distance*1.125); //added the *1.125 to make the distance correct, check with M1013
			}
		}
		delete scores;
	}
	delete image;
	delete thresholdImage;
	delete filteredImage;
	
}
bool Vision::checkTargetHot(TargetReport target)
{
	bool hot = true;
	hot &= target.tapeWidthScore >= TAPE_WIDTH_LIMIT;
	hot &= target.verticalScore >= VERTICAL_SCORE_LIMIT;
	hot &= (target.leftScore > LR_SCORE_LIMIT) | (target.rightScore > LR_SCORE_LIMIT);
	return hot;
}
