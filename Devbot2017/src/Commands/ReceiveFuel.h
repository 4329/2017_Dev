#ifndef RECEIVEFUEL_H
#define RECEIVEFUEL_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class ReceiveFuel: public Command {
public:
	ReceiveFuel();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
