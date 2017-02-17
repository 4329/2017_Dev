#include "OpenFlap.h"


OpenFlap::OpenFlap(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::gearholder.get());
}

// Called just before this Command runs the first time
void OpenFlap::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void OpenFlap::Execute() {
	Robot::gearholder->GearFlap_Forward();
}

// Make this return true when this Command no longer needs to run execute()
bool OpenFlap::IsFinished() {
    if (Robot::oi->getFlapButton()->Get())
    return false;
    return true;
}

// Called once after isFinished returns true
void OpenFlap::End() {
	Robot::gearholder->GearFlap_Backward();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void OpenFlap::Interrupted() {

}
