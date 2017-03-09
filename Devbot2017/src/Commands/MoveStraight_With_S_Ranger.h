#ifndef MOVESTRAIGHT_WITH_S_RANGER_H
#define MOVESTRAIGHT_WITH_S_RANGER_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


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
};

#endif
