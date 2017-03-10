#include "ToggleCamera.h"
#include "../Subsystems/Video.h"

ToggleCamera::ToggleCamera(): InstantCommand() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());S
	//Requires(Robot::video.get());
}

// Called just before this Command runs the first time
void ToggleCamera::Initialize()
{
	if (Robot::cc.SelectedCamera == 0)
	{
		Robot::cc.SelectedCamera = 1;
		SmartDashboard::PutString("Active Camera", "Cam1");
	} else
	{
		Robot::cc.SelectedCamera = 0;
		SmartDashboard::PutString("Active Camera", "Cam2");
	}
	Robot::cc.changeCount++;
}
