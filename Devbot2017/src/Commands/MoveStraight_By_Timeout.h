#ifndef MOVESTRAIGHT_BY_TIMEOUT_H
#define MOVESTRAIGHT_BY_TIMEOUT_H


#include "Commands/Subsystem.h"
#include "../Robot.h"


class MoveStraight_By_Timeout: public Command {
public:
	MoveStraight_By_Timeout(float timeout, float output);

	virtual void Initialize();
	virtual void Execute();
	virtual bool IsFinished();
	virtual void End();
	virtual void Interrupted();

private:
	float _timeout;
	float _output;	//Positive output moves robot in the gear holder direction
					//negative output moves robot in the fuel intake direction
};

#endif
