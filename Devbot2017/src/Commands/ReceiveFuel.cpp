#include "ReceiveFuel.h"


ReceiveFuel::ReceiveFuel(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::gateKeeper.get());
}

// Called just before this Command runs the first time
void ReceiveFuel::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ReceiveFuel::Execute() {
	Robot::gateKeeper->ReceiveFuel();
}

// Make this return true when this Command no longer needs to run execute()
bool ReceiveFuel::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void ReceiveFuel::End() {
	Robot::gateKeeper->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ReceiveFuel::Interrupted() {

}
