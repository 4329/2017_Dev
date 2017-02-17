#ifndef RELEASEGEAR_H
#define RELEASEGEAR_H

#include "Commands/Subsystem.h"
#include "../Robot.h"


class ReleaseGear: public InstantCommand {
public:
	ReleaseGear();

	virtual void Initialize();

private:

};

#endif
