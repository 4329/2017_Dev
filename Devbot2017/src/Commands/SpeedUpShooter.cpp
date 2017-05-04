#include "SpeedUpShooter.h"


SpeedUpShooter::SpeedUpShooter(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::shooter.get());
	Requires(Robot::shooterIndex.get());
}


// Called just before this Command runs the first time
void SpeedUpShooter::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void SpeedUpShooter::Execute() {
	Robot::shooter->RunSpeed();
	Robot::shooterIndex->Stop();	//so index isn't running
}

// Make this return true when this Command no longer needs to run execute()
bool SpeedUpShooter::IsFinished() {
	bool stop = Robot::shooter->CorrectRPM();

	//stop if shooter button is released
	if ( ! Robot::oi->getShootButton()->Get()) {
		Robot::shooter->Stop();
		return true;
	}

    return stop;
}

// Called once after isFinished returns true
void SpeedUpShooter::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void SpeedUpShooter::Interrupted() {

}
