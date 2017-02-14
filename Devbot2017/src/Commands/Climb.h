/*
 * Climb.h
 *
 *  Created on: Feb 7, 2017
 *      Author: josie
 */

#ifndef SRC_COMMANDS_CLIMB_H_
#define SRC_COMMANDS_CLIMB_H_

#include "Commands/Subsystem.h"
#include "../Robot.h"

class Climb: public Command {
public:
	Climb();

		virtual void Initialize();
		virtual void Execute();
		virtual bool IsFinished();
		virtual void End();
		virtual void Interrupted();

private:


};

#endif /* SRC_COMMANDS_CLIMB_H_ */
