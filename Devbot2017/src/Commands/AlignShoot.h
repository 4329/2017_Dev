#ifndef ALIGNSHOOT_H
#define ALIGNSHOOT_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class AlignShoot: public Command {
public:
	AlignShoot();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	float output;
	int16_t distance;
};

#endif
