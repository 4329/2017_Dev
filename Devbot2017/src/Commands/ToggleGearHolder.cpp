#include "ToggleGearHolder.h"


ToggleGearHolder::ToggleGearHolder(): InstantCommand() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::gearholder.get());
}

// Called once when this command runs
void ToggleGearHolder::Initialize() {
	Robot::gearholder->ToggleGearHolder();
}
