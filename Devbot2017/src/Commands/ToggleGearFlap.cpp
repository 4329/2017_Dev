#include "ToggleGearFlap.h"



ToggleGearFlap::ToggleGearFlap(): InstantCommand() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());

	Requires(Robot::gearholder.get());
}

// Called once when this command runs
void ToggleGearFlap::Initialize() {
	Robot::gearholder->ToggleGearFlap();
}

