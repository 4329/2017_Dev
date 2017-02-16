#ifndef RUNSINDEX_H
#define RUNSINDEX_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class RunIndex: public Command {
public:
	RunIndex();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
