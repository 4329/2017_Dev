#include "SpeedUpIndex.h"


SpeedUpIndex::SpeedUpIndex(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::shooterIndex.get());
}


// Called just before this Command runs the first time
void SpeedUpIndex::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void SpeedUpIndex::Execute() {
	Robot::shooterIndex->ForwardVoltage();
}

// Make this return true when this Command no longer needs to run execute()
bool SpeedUpIndex::IsFinished() {
    return Robot::shooterIndex->CorrectRPM();
}

// Called once after isFinished returns true
void SpeedUpIndex::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpeedUpIndex::Interrupted() {

}
