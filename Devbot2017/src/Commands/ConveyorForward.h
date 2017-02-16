#ifndef CONVEYORFORWARD_H
#define CONVEYORFORWARD_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class ConveyorForward: public Command {
public:
	ConveyorForward();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
