#ifndef ALIGNGEAR_H
#define ALIGNGEAR_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class AlignGear: public Command {
public:
	AlignGear();

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	float output;
	double distance;
	bool clockwise;	//tell whihc direction the robot should turn just in case it doesn't see any blocks
};

#endif
