/*
 * Intake.cpp
 *
 *  Created on: Jan 27, 2017
 *      Author: Kurti
 */

#include "Intake.h"

Intake::Intake() : Subsystem("Intake") {
	intakeMotor = RobotMap::intakeMotor;
}

void Intake::InitDefaultCommand() {
	SetDefaultCommand(new FuelIntake());
	SetDefaultCommand(new FuelOuttake());
}

void Intake::Configuration() {
//add config stuff here
	intakeMotor->SetInverted(false);
	//intakeMotor->SetVoltageRamp();
}

float Intake::Limit(float num) {
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
	float nValue = Limit(trigger_axis);
	std::cout << "Intake right trigger axis: " << nValue << std::endl;

	intakeMotor->Set(nValue);
	std::cout << "Intake voltage: " << intakeMotor->GetBatteryVoltage() << std::endl;
}

void Intake::fuel_outtake(float trigger_axis) {
	float nValue = Limit(trigger_axis);
	std::cout << "Intake left trigger axis: " << nValue << std::endl;

	intakeMotor->Set(-nValue);
	std::cout << "Intake voltage: " << intakeMotor->GetBatteryVoltage() << std::endl;
}

void Intake::StopMotor() {
	intakeMotor->Set(0);
}
