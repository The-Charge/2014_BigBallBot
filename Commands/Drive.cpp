// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "Drive.h"
#include "String.h"

Drive::Drive() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::driveTrain);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	sc = new SendableChooser();
	cDrive = new std::string("c");
	aDrive = new std::string("a");
	tDrive = new std::string("t");
	xDrive = new std::string("x");
	sc->AddDefault("Clayton Drive", cDrive);
	sc->AddObject("Arcade Drive", aDrive);
	sc->AddObject("Tank Drive (2 Joy)", tDrive);
	sc->AddObject("Tank Drive(XBox)", xDrive);
	SmartDashboard::PutData("Drive mode chooser", sc);
    //SmartDashboard::putData("Drive mode chooser", sc);
}
// Called just before this Command runs the first time
void Drive::Initialize() {
	Robot::driveTrain->SetLeft(0);
	Robot::driveTrain->SetRight(0);	
}
// Called repeatedly when this Command is scheduled to run
void Drive::Execute() 
{
	//Send the speeds to the drive-train.
	std::string *selected = (std::string*)sc->GetSelected();
	float leftSpeed = 0;
	float rightSpeed = 0;
	if(selected->compare(*cDrive) == 0)
	{
		printf("======Clayton drive======");
		leftSpeed   = (Robot::oi->getDriverJoystick()->GetY()) + (Robot::oi->getDriverJoystick()->GetThrottle());
		rightSpeed  = (Robot::oi->getDriverJoystick()->GetY()) - (Robot::oi->getDriverJoystick()->GetThrottle());
	}
	else if(selected->compare(*aDrive) == 0)
	{
		printf("======Arcade drive======");
		leftSpeed   = (Robot::oi->getDriverJoystick()->GetY()) + (Robot::oi->getDriverJoystick()->GetX());
		rightSpeed  = (Robot::oi->getDriverJoystick()->GetY()) - (Robot::oi->getDriverJoystick()->GetX());
	}
	else if(selected->compare(*tDrive) == 0)
	{
		printf("======Tank drive======");
		leftSpeed = Robot::oi->getDriverJoystick()->GetY();
		rightSpeed = Robot::oi->getShooterJoystick()->GetY();
	}
	else
	{
		printf("======XBox drive======");
		leftSpeed = Robot::oi->getDriverJoystick()->GetY();
		rightSpeed = Robot::oi->getDriverJoystick()->GetRawAxis(5);
	}
	
	
	Robot::driveTrain->SetLeft(leftSpeed);
	Robot::driveTrain->SetRight(rightSpeed);
}
// Make this return true when this Command no longer needs to run execute()
bool Drive::IsFinished() {
	return false;
}
// Called once after isFinished returns true
void Drive::End() {
	Robot::driveTrain->SetLeft(0);
	Robot::driveTrain->SetRight(0);	
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Drive::Interrupted() {
	End();
}
