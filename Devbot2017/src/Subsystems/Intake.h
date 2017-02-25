/*
 * Intake.h
 *
 *  Created on: Jan 27, 2017
 *      Author: Kurtis
 */

#ifndef SRC_SUBSYSTEMS_INTAKE_H_
#define SRC_SUBSYSTEMS_INTAKE_H_
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"
#include "../RobotMap.h"

class Intake : public Subsystem {
public:
	Intake();
	void InitDefaultCommand();
	void Configuration();

	void fuel_intake(float trigger_axis);
	void fuel_outtake(float trigger_axis);
	void StopMotor();

	float Limit(float num);

private:
	std::shared_ptr<CANTalon> intakeMotor;
};


#endif /* SRC_SUBSYSTEMS_INTAKE_H_ */
