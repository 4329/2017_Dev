#include "ToggleGearHolder.h"


ToggleGearHolder::ToggleGearHolder() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::gearholder.get());
}


void ToggleGearHolder::Initialize() {
	Robot::gearholder->ToggleGearHolder();
}
