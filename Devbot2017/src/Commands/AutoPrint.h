#ifndef AUTOPRINT_H
#define AUTOPRINT_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class AutoPrint: public InstantCommand {
public:
	AutoPrint(std::string autoMode);

	virtual void Initialize();

private:
	std::string _autoMode;
};

#endif
