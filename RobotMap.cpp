// RobotBuilder Version: 1.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in th future.
#include "RobotMap.h"
#include "LiveWindow/LiveWindow.h"
// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
Encoder* RobotMap::driveTrainRightEncoder = NULL;
CANJaguar* RobotMap::driveTrainFrontLeftMotor = NULL;
CANJaguar* RobotMap::driveTrainCenterLeftMotor = NULL;
CANJaguar* RobotMap::driveTrainRearLeftMotor = NULL;
CANJaguar* RobotMap::driveTrainFrontRightMotor = NULL;
CANJaguar* RobotMap::driveTrainCenterRightMotor = NULL;
CANJaguar* RobotMap::driveTrainRearRightMotor = NULL;
Encoder* RobotMap::driveTrainLeftEncoder = NULL;
DoubleSolenoid* RobotMap::shifterShifter = NULL;
Compressor* RobotMap::airCompressorAirCompressor = NULL;
DoubleSolenoid* RobotMap::pickupArmsLeftShortCylinder = NULL;
DoubleSolenoid* RobotMap::pickupArmsLeftLongCylinder = NULL;
DoubleSolenoid* RobotMap::pickupArmsRightShortCylinder = NULL;
DoubleSolenoid* RobotMap::pickupArmsRightLongCylinder = NULL;
CANJaguar* RobotMap::throwerThrowerMotor = NULL;
DigitalInput* RobotMap::throwerThrowerLimit = NULL;
CANJaguar* RobotMap::pickupWheelsRightPickupWheel = NULL;
CANJaguar* RobotMap::pickupWheelsLeftPickupWheel = NULL;
AnalogChannel* RobotMap::distanceUltrasonic = NULL;
DigitalOutput* RobotMap::lEDTeamNumber = NULL;
DigitalOutput* RobotMap::lEDTimer = NULL;
DigitalOutput* RobotMap::lEDDistance = NULL;
CANJaguar* RobotMap::clockspringsMotor = NULL;
AnalogChannel* RobotMap::clockspringsPot = NULL;
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=ALLOCATION
void RobotMap::init() {
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	LiveWindow* lw = LiveWindow::GetInstance();
	driveTrainRightEncoder = new Encoder(1, 2, 1, 3, false, Encoder::k4X);
	lw->AddSensor("DriveTrain", "Right Encoder", driveTrainRightEncoder);
	driveTrainRightEncoder->SetDistancePerPulse(0.01);
        driveTrainRightEncoder->SetPIDSourceParameter(Encoder::kRate);
        driveTrainRightEncoder->Start();
	driveTrainFrontLeftMotor = new CANJaguar(6);
	
	
	driveTrainCenterLeftMotor = new CANJaguar(14);
	
	
	driveTrainRearLeftMotor = new CANJaguar(5);
	
	
	driveTrainFrontRightMotor = new CANJaguar(4);
	
	
	driveTrainCenterRightMotor = new CANJaguar(13);
	
	
	driveTrainRearRightMotor = new CANJaguar(3);
	
	
	driveTrainLeftEncoder = new Encoder(1, 6, 1, 5, false, Encoder::k4X);
	lw->AddSensor("DriveTrain", "Left Encoder", driveTrainLeftEncoder);
	driveTrainLeftEncoder->SetDistancePerPulse(0.01);
        driveTrainLeftEncoder->SetPIDSourceParameter(Encoder::kRate);
        driveTrainLeftEncoder->Start();
	shifterShifter = new DoubleSolenoid(1, 1, 2);      
	
	
	airCompressorAirCompressor = new Compressor(1, 4, 1, 1);
	
	
	pickupArmsLeftShortCylinder = new DoubleSolenoid(1, 3, 4);      
	
	
	pickupArmsLeftLongCylinder = new DoubleSolenoid(1, 5, 6);      
	
	
	pickupArmsRightShortCylinder = new DoubleSolenoid(2, 3, 4);      
	
	
	pickupArmsRightLongCylinder = new DoubleSolenoid(2, 5, 6);      
	
	
	throwerThrowerMotor = new CANJaguar(11);
	
	
	throwerThrowerLimit = new DigitalInput(1, 8);
	lw->AddSensor("Thrower", "Thrower Limit", throwerThrowerLimit);
	
	pickupWheelsRightPickupWheel = new CANJaguar(7);
	
	
	pickupWheelsLeftPickupWheel = new CANJaguar(15);
	
	
	distanceUltrasonic = new AnalogChannel(1, 2);
	lw->AddSensor("Distance", "Ultrasonic", distanceUltrasonic);
	
	lEDTeamNumber = new DigitalOutput(1, 12);
	
	
	lEDTimer = new DigitalOutput(1, 14);
	
	
	lEDDistance = new DigitalOutput(1, 13);
	
	
	clockspringsMotor = new CANJaguar(8);
	
	
	clockspringsPot = new AnalogChannel(1, 3);
	lw->AddSensor("Clocksprings", "Pot", clockspringsPot);
	
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
	// Overwrite CAN Jaguar ID assignments to run code in Frisbee Bot.
	
	
	
	
	
}
