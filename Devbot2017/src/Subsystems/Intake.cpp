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

}

void Intake::Configuration() {
//add config stuff here
	intakeMotor->SetInverted(false);
	//intakeMotor->SetVoltageRamp();
}

void Intake::fuel_intake() {
	intakeMotor->Set(1);
	std::cout << "Intake voltage: " << intakeMotor->GetBatteryVoltage() << std::endl;
}

void Intake::fuel_outtake() {
	intakeMotor->Set(-1);
	std::cout << "Intake voltage: " << intakeMotor->GetBatteryVoltage() << std::endl;
}

void Intake::StopMotor() {
	intakeMotor->Set(0);
}
