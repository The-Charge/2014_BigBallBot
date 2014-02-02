// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "ThrowerShoot.h"
ThrowerShoot::ThrowerShoot() {
	// Use requires() here to declare subsystem dependencies
	// eg. requires(chassis);
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::thrower);
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// Called just before this Command runs the first time
void ThrowerShoot::Initialize() {
	SetTimeout(.2);
}
// Called repeatedly when this Command is scheduled to run
void ThrowerShoot::Execute() {
	Robot::thrower->Shoot();

}
// Make this return true when this Command no longer needs to run execute()
bool ThrowerShoot::IsFinished() {
	float position = Robot::thrower->GetPosition();
	return (IsTimedOut() && ( position > LEFT_BOUND_COCK && position < RIGHT_BOUND_COCK ));

}
// Called once after isFinished returns true
void ThrowerShoot::End() {
	Robot::thrower->Stop();

}
// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ThrowerShoot::Interrupted() {
	Robot::thrower->Stop();

}
