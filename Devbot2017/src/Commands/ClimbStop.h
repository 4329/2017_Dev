#ifndef SRC_COMMANDS_CLIMBSTOP_H_
#define SRC_COMMANDS_CLIMBSTOP_H_

#include "Commands/Subsystem.h"
#include "../Robot.h"
#include "../RobotMap.h"
#include "../OI.h"


class ClimbStop: public Command {
public:
	ClimbStop();

		virtual void Initialize();
		virtual void Execute();
		virtual bool IsFinished();
		virtual void End();
		virtual void Interrupted();

private:


};

#endif /* SRC_COMMANDS_CLIMB_H_ */
