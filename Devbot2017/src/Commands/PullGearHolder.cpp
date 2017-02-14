#include "PullGearHolder.h"


PullGearHolder::PullGearHolder(): InstantCommand() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::gearholder.get());
}

// Called just before this Command runs the first time
void PullGearHolder::Initialize() {
	Robot::gearholder->PullGearHolder();
}

