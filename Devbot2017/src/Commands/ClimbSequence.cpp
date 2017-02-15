#include "ClimbSequence.h"
#include "PushGearHolder.h"
#include "Delay.h"
#include "Vent.h"
#include "PullGearHolder.h"
#include "Climb.h"


ClimbSequence::ClimbSequence() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::climb.get());
	Requires(Robot::gearholder.get());

	AddSequential(new PushGearHolder());
	AddSequential(new Delay(1));
	AddSequential(new Vent());
	AddSequential(new PullGearHolder());
	AddParallel(new Climb());
}
