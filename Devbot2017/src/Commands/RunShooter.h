#ifndef RUNSHOOTER_H
#define RUNSHOOTER_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class RunShooter: public Command {
public:
	RunShooter();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
