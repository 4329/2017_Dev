#include "ConveyorBackward.h"


ConveyorBackward::ConveyorBackward(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::conveyorBelt.get());
}

// Called just before this Command runs the first time
void ConveyorBackward::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ConveyorBackward::Execute() {
	Robot::conveyorBelt->Backward();
}

// Make this return true when this Command no longer needs to run execute()
bool ConveyorBackward::IsFinished() {
    //if (Robot::oi->getConveyorBackwardButton()->Get())
    return false;
    //return true;
}

// Called once after isFinished returns true
void ConveyorBackward::End() {
	Robot::conveyorBelt->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ConveyorBackward::Interrupted() {

}
