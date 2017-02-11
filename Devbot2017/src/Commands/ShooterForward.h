#ifndef SHOOTERFORWARD_H
#define SHOOTERFORWARD_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class ShooterForward: public Command {
public:
	ShooterForward();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
