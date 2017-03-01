#include "MoveStraight.h"

MoveStraight::MoveStraight(): Command() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::driveTrain.get());
}

// Called just before this Command runs the first time
void MoveStraight::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void MoveStraight::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool MoveStraight::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void MoveStraight::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveStraight::Interrupted() {

}
