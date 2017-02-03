#ifndef PULLGEARHOLDER_H
#define PULLGEARHOLDER_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

class PullGearHolder: public Command {
public:
	PullGearHolder();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
