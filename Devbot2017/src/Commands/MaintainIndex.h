#ifndef MAINTAININDEX_H
#define MAINTAININDEX_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class MaintainIndex: public Command {
public:
	MaintainIndex();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
