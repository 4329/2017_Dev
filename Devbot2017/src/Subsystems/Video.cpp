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
	//SetDefaultCommand(new ToggleCamera());
}

void Video::VideoFeed() {
	/*
	int cameraDev;

	//set which camera is being used
	if (GearCamOn) {
		cameraDev = gearDev;
	}
	else {
		cameraDev = forwardDev;
	}
	*/
	// Get the USB camera from CameraServer
	//cs::UsbCamera camera = frc::CameraServer::GetInstance()->StartAutomaticCapture(/*cameraDev*/);
	// Set the resolution
	//camera.SetResolution(640, 480);

	camera1 = CameraServer::GetInstance()->StartAutomaticCapture(0);
	camera2 = CameraServer::GetInstance()->StartAutomaticCapture(1);
	server = CameraServer::GetInstance()->GetServer();
	  // dummy sinks to keep camera connections open
	camera1.SetResolution(320, 240);
	camera2.SetResolution(320, 240);
	camera1.SetFPS(15);
	camera2.SetFPS(15);
	cvsink1 = new cs::CvSink("GearCam");
	cvsink1->SetSource(camera1);
	cvsink1->SetEnabled(true);
	cvsink2 = new cs::CvSink("ShooterCam");
	cvsink2->SetSource(camera2);
	cvsink2->SetEnabled(true);
}

void Video::_ToggleCamera() {
	GearCamOn = !GearCamOn;

	if (GearCamOn)
	{
		server.SetSource(camera1);
	} else
	{
		server.SetSource(camera2);
	}
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
