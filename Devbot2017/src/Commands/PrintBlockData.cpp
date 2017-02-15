#include "PrintBlockData.h"


PrintBlockData::PrintBlockData(): InstantCommand() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::shooterPixy.get());
}


// Called just before this Command runs the first time
void PrintBlockData::Initialize() {
	Robot::shooterPixy->printBlockData();
}

