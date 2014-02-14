// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "OI.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutoPreShoot.h"
#include "Commands/AutoShoot.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/CheckHot.h"
#include "Commands/ClockspringsHigh.h"
#include "Commands/ClockspringsLow.h"
#include "Commands/CompressorRun.h"
#include "Commands/Drive.h"
#include "Commands/PickupArmsExtend.h"
#include "Commands/PickupArmsMidwayHi.h"
#include "Commands/PickupArmsMidwayLo.h"
#include "Commands/PickupArmsRetract.h"
#include "Commands/PickupWheelsForward.h"
#include "Commands/PickupWheelsOff.h"
#include "Commands/PickupWheelsReverseFast.h"
#include "Commands/PickupWheelsReverseSlow.h"
#include "Commands/ResetDriveJags.h"
#include "Commands/ResetJags.h"
#include "Commands/ShifterHigh.h"
#include "Commands/ShifterLow.h"
#include "Commands/ShowDistance.h"
#include "Commands/ShowTeam.h"
#include "Commands/ShowTime.h"
#include "Commands/ThrowerShoot.h"
#include "Commands/ThrowerUp.h"
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
OI::OI() {
	// Process operator interface input here.
        // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	shooterJoystick = new Joystick(2);
	
	driverJoystick = new Joystick(1);
	
	shiftHighButton = new JoystickButton(driverJoystick, 1);
	shiftHighButton->WhenPressed(new ShifterHigh());
	shiftLowButton = new JoystickButton(driverJoystick, 2);
	shiftLowButton->WhenPressed(new ShifterLow());
     
        // SmartDashboard Buttons
	SmartDashboard::PutData("Show Time", new ShowTime());
	SmartDashboard::PutData("Show Distance", new ShowDistance());
	SmartDashboard::PutData("Show Team", new ShowTeam());
	SmartDashboard::PutData("Pickup Wheels Off", new PickupWheelsOff());
	SmartDashboard::PutData("Pickup Wheels Forward", new PickupWheelsForward());
	SmartDashboard::PutData("Pickup Wheels Reverse Slow", new PickupWheelsReverseSlow());
	SmartDashboard::PutData("Pickup Wheels Reverse Fast", new PickupWheelsReverseFast());
	SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
	SmartDashboard::PutData("Drive", new Drive());
	SmartDashboard::PutData("ShifterHigh", new ShifterHigh());
	SmartDashboard::PutData("ShifterLow", new ShifterLow());
	SmartDashboard::PutData("CompressorRun", new CompressorRun());
	SmartDashboard::PutData("Pickup Arms Extend", new PickupArmsExtend());
	SmartDashboard::PutData("Pickup Arms Retract", new PickupArmsRetract());
	SmartDashboard::PutData("Pickup Arms Midway Hi", new PickupArmsMidwayHi());
	SmartDashboard::PutData("Pickup Arms Midway Lo", new PickupArmsMidwayLo());
	SmartDashboard::PutData("Thrower Shoot", new ThrowerShoot());
	SmartDashboard::PutData("Thrower Up", new ThrowerUp());
	SmartDashboard::PutData("Clocksprings High", new ClockspringsHigh());
	SmartDashboard::PutData("Clocksprings Low", new ClockspringsLow());
	SmartDashboard::PutData("Reset Drive Jags", new ResetDriveJags());
	SmartDashboard::PutData("Reset Jags", new ResetJags());
	SmartDashboard::PutData("Check Hot", new CheckHot());
	SmartDashboard::PutData("AutoPreShoot", new AutoPreShoot());
	SmartDashboard::PutData("AutoShoot", new AutoShoot());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
Joystick* OI::getShooterJoystick() {
	return shooterJoystick;
}
Joystick* OI::getDriverJoystick() {
	return driverJoystick;
}
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=FUNCTIONS
	 
