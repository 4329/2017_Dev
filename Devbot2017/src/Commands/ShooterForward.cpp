#include "ShooterForward.h"

ShooterForward::ShooterForward(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());

}

// Called just before this Command runs the first time
void ShooterForward::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ShooterForward::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool ShooterForward::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void ShooterForward::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ShooterForward::Interrupted() {

}
