#ifndef ROTATE_H
#define ROTATE_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class Rotate: public Command {
public:
	Rotate(float Angle);

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	float correctYaw;
	float targetAngle;
	float output;
	float error;
};

#endif
