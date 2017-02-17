#ifndef OPENFLAP_H
#define OPENFLAP_H

#include "Commands/Subsystem.h"
#include "../Robot.h"


class OpenFlap: public Command {
public:
	OpenFlap();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
