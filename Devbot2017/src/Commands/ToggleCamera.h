#ifndef TOGGLECAMERA_H
#define TOGGLECAMERA_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class ToggleCamera: public InstantCommand {
public:
	ToggleCamera();

	virtual void Initialize();

private:

};

#endif
