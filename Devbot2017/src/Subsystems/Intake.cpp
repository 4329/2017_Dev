/*
 * Intake.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: Kurti
 */

#include "Intake.h"
#include "../Commands/FuelIntake.h"

Intake::Intake() : Subsystem("Intake") {
	intakeMotor = RobotMap::intakeMotor;

	Configuration();
}

void Intake::InitDefaultCommand() {
	SetDefaultCommand(new FuelIntake());	//setDefaultCommand is used to run commands that take axis values
	//SetDefaultCommand(new FuelOuttake());

}

void Intake::Configuration() {
//add config stuff here
	intakeMotor->SetInverted(false);
	//intakeMotor->SetVoltageRamp();
}

float Intake::Limit(float num) {	//sets number to correct value if it's over 1 or under 0
									//( trigger value is usually between 1 and 0, but may be otherwise)
	if (num > 1) {
		return 1;
	}
	else if (num < 0) {
		return 0;
	}
	else {
		return num;
	}
}

void Intake::fuel_intake(float trigger_axis) {
	float nValue = Limit(trigger_axis);	//get right trigger axis value
	std::cout << "4329 Log: " << GetTime() << ", Intake right trigger axis: " << nValue << std::endl;	//print axis value

	intakeMotor->Set(-nValue);	//set motor value ( number will betweeen the deadzone and 1)
	std::cout << "Intake: voltage: " << intakeMotor->GetOutputVoltage() << "  ";	//print voltage
	std::cout << "current: " << intakeMotor->GetOutputCurrent() << std::endl;	//print current
}

void Intake::fuel_outtake(float trigger_axis) {
	float nValue = Limit(trigger_axis);	//get left trigger axis value
	std::cout << "4329 Log: " << GetTime() << ", Intake left trigger axis: " << nValue << std::endl;	//print axis value

	intakeMotor->Set(nValue);	//set motor value ( number will be between -deadzone and -1
	std::cout << "Intake: voltage: " << intakeMotor->GetOutputVoltage() << "  ";	//print voltage
	std::cout << "current: " << intakeMotor->GetOutputCurrent() << std::endl;	//print current
}

void Intake::StopMotor() {
	intakeMotor->Set(0);	//setting motor to 0 stops the motor
}
