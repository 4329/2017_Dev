#include "Video.h"

#include "../Commands/ToggleCamera.h"

#include <CameraServer.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>

Video::Video() : Subsystem("Video"){
	GearCamOn = true;
	TriggerPressed = false;

	gearDev = 0;
	forwardDev = 1;
}

void Video::InitDefaultCommand() {
	SetDefaultCommand(new ToggleCamera());
}

void Video::VideoFeed() {

	int cameraDev;

	//set which camera is being used
	if (GearCamOn) {
		cameraDev = gearDev;
	}
	else {
		cameraDev = forwardDev;
	}

	// Get the USB camera from CameraServer
	cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture(cameraDev);
	// Set the resolution
	camera.SetResolution(640, 480);
}

void Video::_ToggleCamera() {
	GearCamOn = !GearCamOn;
}

int Video::GetForwardDev() {
	return forwardDev;
}

int Video::GetGearDev() {
	return gearDev;
}

bool Video::GetTriggerPressed() {
	return TriggerPressed;
}

void Video::SetTriggerpressed(bool set) {
	TriggerPressed = false;
}
