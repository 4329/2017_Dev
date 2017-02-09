#ifndef SPEEDUPSHOOTER_H
#define SPEEDUPSHOOTER_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class SpeedUpShooter: public Command {
public:
	SpeedUpShooter();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
