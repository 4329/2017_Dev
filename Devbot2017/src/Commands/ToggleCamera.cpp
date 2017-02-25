#include "ToggleCamera.h"

ToggleCamera::ToggleCamera(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());S
	Requires(Robot::video.get());
}

// Called just before this Command runs the first time
void ToggleCamera::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void ToggleCamera::Execute() {
	float triggerValue = Robot::oi->GetAxisValue(Robot::oi->getRobotDriver(), OI::Xbox_Axis_Right_Trigger);

	//only toggle cameras when trigger goes from being not pressed to pressed
	if ( ! Robot::video->GetTriggerPressed()) {

			if (triggerValue != 0) {
				Robot::video->SetTriggerpressed(true);

				Robot::video->_ToggleCamera();
				std::cout << "switched camera" << std::endl;
			}
	}
	if (triggerValue == 0) {
			Robot::video->SetTriggerpressed(false);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool ToggleCamera::IsFinished() {
    return false;
}

// Called once after isFinished returns true
void ToggleCamera::End() {

}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void ToggleCamera::Interrupted() {

}
