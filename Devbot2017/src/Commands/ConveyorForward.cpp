#include "ConveyorForward.h"


ConveyorForward::ConveyorForward(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::conveyorBelt.get());
}

// Called just before this Command runs the first time
void ConveyorForward::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ConveyorForward::Execute() {
	Robot::conveyorBelt->Forward();
}

// Make this return true when this Command no longer needs to run execute()
bool ConveyorForward::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void ConveyorForward::End() {
	Robot::conveyorBelt->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ConveyorForward::Interrupted() {

}
