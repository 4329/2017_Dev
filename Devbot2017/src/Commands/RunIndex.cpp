#include "RunIndex.h"


RunIndex::RunIndex(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::shooterIndex.get());
}

// Called just before this Command runs the first time
void RunIndex::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RunIndex::Execute() {
	Robot::shooterIndex->RunVoltage();
}

// Make this return true when this Command no longer needs to run execute()
bool RunIndex::IsFinished() {
    if (Robot::oi->getShootButton()->Get())
    return false;
    return true;
}

// Called once after isFinished returns true
void RunIndex::End() {
	Robot::shooterIndex->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunIndex::Interrupted() {

}
