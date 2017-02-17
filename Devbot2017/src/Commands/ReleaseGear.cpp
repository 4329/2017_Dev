#include "ReleaseGear.h"


ReleaseGear::ReleaseGear() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::gearholder.get());
}


void ReleaseGear::Initialize() {
	Robot::gearholder->ToggleGearHolder();
}
