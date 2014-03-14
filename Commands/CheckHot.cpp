// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "CheckHot.h"
#include "Vision/AxisCamera.h"
#include "WPILib.h"
#include <Timer.h>
CheckHot::CheckHot()
{
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::vision);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// Called just before this Command runs the first time
void CheckHot::Initialize() {
	printf("begin checkhot: %f\n",Timer::GetFPGATimestamp());
	SetTimeout(6.0);
}
// Called repeatedly when this Command is scheduled to run
void CheckHot::Execute() {
	printf("exe: %f\n",Timer::GetFPGATimestamp());
	Robot::vision->fetchImage();
	SmartDashboard::PutBoolean("IsHot",Robot::vision->isHot());
}
// Make this return true when this Command no longer needs to run execute()
bool CheckHot::IsFinished() {
	if (Robot::vision->isHot() || IsTimedOut()){
		printf("finish checkhot: %f\n",Timer::GetFPGATimestamp());
		return true;
	} else {
		return false;
	}
}
// Called once after isFinished returns true
void CheckHot::End() {
	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void CheckHot::Interrupted() {
	End();
}
