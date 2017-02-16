#ifndef CONVEYORBACKWARD_H
#define CONVEYORBACKWARD_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class ConveyorBackward: public Command {
public:
	ConveyorBackward();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
