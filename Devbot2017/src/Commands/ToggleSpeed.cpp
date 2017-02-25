#include "ToggleSpeed.h"



ToggleSpeed::ToggleSpeed(): InstantCommand() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());

	//doesn't require anything
}

// Called once when this command runs
void ToggleSpeed::Initialize() {
	Robot::driveTrain->ToggleHighSpeed();

	SmartDashboard::PutBoolean("HighSpeed", Robot::driveTrain->GetHighSpeed());
}

