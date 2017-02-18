#include "ClimbSequence.h"
#include "PushGearHolder.h"
#include "Delay.h"
#include "Vent_On.h"
#include "PullGearHolder.h"
#include "Climb.h"


ClimbSequence::ClimbSequence() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::climb.get());
	Requires(Robot::gearholder.get());

	//possibly skip first 4 steps if already climbed
	AddSequential(new PushGearHolder());
	AddSequential(new Delay(1));
	AddSequential(new Vent_On());
	AddSequential(new PullGearHolder());
	AddParallel(new Climb());
}
