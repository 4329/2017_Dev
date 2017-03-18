#include "ToggleFloorGear.h"



ToggleFloorGear::ToggleFloorGear(): InstantCommand() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::floorGear.get());
}

// Called once when this command runs
void ToggleFloorGear::Initialize() {
	Robot::floorGear->ToggleFloorGear();
}

