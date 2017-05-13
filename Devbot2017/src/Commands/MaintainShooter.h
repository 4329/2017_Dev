#ifndef MAINTAINSHOOTER_H
#define MAINTAINSHOOTER_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class MaintainShooter: public Command {
public:
	MaintainShooter();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
