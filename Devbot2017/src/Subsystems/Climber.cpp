/*
 * Climber.cpp
 *
 *  Created on: Feb 7, 2017
 *      Author: josie
 */

#include "Climber.h"
#include "../RobotMap.h"
#include "../Robot.h"

Climber::Climber() : Subsystem("Climber") {
	climberMotor = RobotMap::climberMotor;
	climberMotor2 = RobotMap::climberMotor2;
	Configuration();
}


void Climber::InitDefaultCommand() {
	//SetDefaultCommand(new Climb_Start());	//setDefaultCommand is used to run commands that take axis values
	//SetDefaultCommand(new FuelOuttake());

}

void Climber::Configuration() {
//add config stuff here
	climberMotor->SetInverted(false);
	climberMotor2->SetInverted(false);

	//set mode
	climberMotor->SetControlMode(CANSpeedController::kPercentVbus);
	climberMotor2->SetControlMode(CANSpeedController::kFollower);

	climberMotor2->Set(10);	//follows the climberMotor

	climberMotor->Enable();
	climberMotor2->Enable();
}


void Climber::climb_start(float voltage) {
	climberMotor->Set(voltage);	//set motor value ( number will betweeen the deadzone and 1)

	//prints voltage and current
	std::cout << "Climber: voltage: " << climberMotor->GetOutputVoltage() << "  ";
	std::cout << "voltage2: " << climberMotor2->GetOutputVoltage() << "  ";
	std::cout << "current: " << climberMotor->GetOutputCurrent() << "  ";
	std::cout << "current2: " << climberMotor2->GetOutputCurrent() << std::endl;
}

void Climber::climb_stop() {
	climberMotor->Set(0);	//setting motor to 0 stops the motor
}

