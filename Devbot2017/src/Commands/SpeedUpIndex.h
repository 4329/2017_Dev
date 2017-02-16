#ifndef SPEEDUPINDEX_H
#define SPEEDUPINDEX_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class SpeedUpIndex: public Command {
public:
	SpeedUpIndex();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
