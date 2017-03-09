#include "AlignShoot.h"

AlignShoot::AlignShoot(): Command() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::driveTrain.get());


}

// Called just before this Command runs the first time
void AlignShoot::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AlignShoot::Execute() {

}

// Make this return true when this Command no longer needs to run execute()
bool AlignShoot::IsFinished() {
	return false;
}

// Called once after isFinished returns true
void AlignShoot::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AlignShoot::Interrupted() {

}
