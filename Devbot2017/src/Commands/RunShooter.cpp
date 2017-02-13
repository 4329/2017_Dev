#include "RunShooter.h"


RunShooter::RunShooter(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::shooter.get());
}

// Called just before this Command runs the first time
void RunShooter::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RunShooter::Execute() {
	Robot::shooter->StartUp();	//set shooter to a certain RPM until shoot command ends
}

// Make this return true when this Command no longer needs to run execute()
bool RunShooter::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void RunShooter::End() {
	Robot::shooter->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunShooter::Interrupted() {

}
