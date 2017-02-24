#ifndef TOGGLESPEED_H
#define TOGGLESPEED_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class ToggleSpeed: public InstantCommand {
public:
	ToggleSpeed();

	virtual void Initialize();

private:

};

#endif

