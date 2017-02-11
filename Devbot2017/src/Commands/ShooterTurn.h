#ifndef SHOOTERTURN_H
#define SHOOTERTURN_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class ShooterTurn: public Command {
public:
	ShooterTurn();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
