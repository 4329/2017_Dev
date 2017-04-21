/*
 * Climber.h
 *
 *  Created on: Feb 7, 2017
 *      Author: josie
 */

#ifndef SRC_SUBSYSTEMS_CLIMBER_H_
#define SRC_SUBSYSTEMS_CLIMBER_H_
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"
#include "../RobotMap.h"

class Climber : public Subsystem {
public:
	Climber();
	void InitDefaultCommand();
	void Configuration();

	void climb_start(float voltage);	//takes in values from -1 to 1
	void climb_stop();

private:
	std::shared_ptr<CANTalon> climberMotor;
	std::shared_ptr<CANTalon> climberMotor2;

};


#endif /* SRC_SUBSYSTEMS_CLIMBER_H_ */
