#include "PushGearHolder.h"


PushGearHolder::PushGearHolder(): InstantCommand() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::gearholder.get());
}


// Called just before this Command runs the first time
void PushGearHolder::Initialize() {
	Robot::gearholder->PushGearHolder();
	std::cout << "pushed the gear holder////////////////////////////////////////////////" << std::endl;
}

