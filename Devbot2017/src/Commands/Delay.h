#ifndef DELAY_H
#define DELAY_H


#include "Commands/Subsystem.h"
#include "../Robot.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class Delay: public WaitCommand {
public:
	Delay(double timeout);

private:

};

#endif
