#include "MoveStraight.h"

MoveStraight::MoveStraight(int index): Command() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::driveTrain.get());
    _index = index;
}

// Called just before this Command runs the first time
void MoveStraight::Initialize() {
	Robot::driveTrain->SetActiveMotionProfile(_index);
	Robot::driveTrain->StartMotionProfile();
	std::cout << "now moving straight" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void MoveStraight::Execute() {
	Robot::driveTrain->MotionControl();
}

// Make this return true when this Command no longer needs to run execute()
bool MoveStraight::IsFinished() {
	return Robot::driveTrain->MotionProfileComplete();
}

// Called once after isFinished returns true
void MoveStraight::End() {
	Robot::driveTrain->StopMotionProfile();
	Robot::driveTrain->StopMotors();
	std::cout << "done moving straight" << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveStraight::Interrupted() {

}
