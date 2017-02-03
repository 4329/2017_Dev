#ifndef PUSHGEARHOLDER_H
#define PUSHGEARHOLDER_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

class PushGearHolder: public Command {
public:
	PushGearHolder();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
