#include "ReleaseGear.h"
#include "Delay.h"
#include "PushGearHolder.h"
#include "PullGearHolder.h"


ReleaseGear::ReleaseGear() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::gearholder.get());

	AddSequential(new PushGearHolder());
	AddSequential(new Delay(0.5));
	AddSequential(new PullGearHolder());
}
