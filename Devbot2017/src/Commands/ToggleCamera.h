#ifndef TOGGLECAMERA_H
#define TOGGLECAMERA_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class ToggleCamera: public Command {
public:
	ToggleCamera();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:

};

#endif
