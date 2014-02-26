// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
//
//
#include "ClockspringsLow.h"
const float DESTINATION = 2.0;
ClockspringsLow::ClockspringsLow() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::clocksprings);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Robot::netTable->PutNumber("ClockspringsLow::destination", DESTINATION);
}
// Called just before this Command runs the first time
void ClockspringsLow::Initialize() {
	double destination = Robot::netTable->GetNumber("ClockspringsLow::destination",DESTINATION);
	Robot::clocksprings->SetDestination(destination);
}
// Called repeatedly when this Command is scheduled to run
void ClockspringsLow::Execute() {
	double destination = Robot::netTable->GetNumber("ClockspringsLow::destination",DESTINATION);
	Robot::clocksprings->SetDestination(destination);
}
// Make this return true when this Command no longer needs to run execute()
bool ClockspringsLow::IsFinished() {
	return Robot::clocksprings->AtDestination();
}
// Called once after isFinished returns true
void ClockspringsLow::End() {
	Robot::clocksprings->Stop();
}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ClockspringsLow::Interrupted() {
}
