#ifndef MOVESTRAIGHT_WITH_S_RANGER_H
#define MOVESTRAIGHT_WITH_S_RANGER_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

//this command is meant to move a certain distance based on the GEAR ultrasonic sensor
class MoveStraight_With_S_Ranger: public Command {
public:
	MoveStraight_With_S_Ranger(bool forward, double cm_target_distance);

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	float output;
	double distance;
	double target_distance;
	bool _forward;
	int count;	//if count is high enough robot will stop
				//count increments by 1 when the distance value is weird (above 1000)
};

#endif
