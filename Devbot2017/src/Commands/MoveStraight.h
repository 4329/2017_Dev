#ifndef MOVESTRAIGHT_H
#define MOVESTRAIGHT_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class MoveStraight: public Command {
public:
	MoveStraight();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
