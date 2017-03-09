#ifndef VIDEO_H
#define VIDEO_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Video : public Subsystem {
public:
	Video();

	void InitDefaultCommand();

	int GetForwardDev();	//get the device number of the forward camera
	int GetGearDev();	//get the device number of the gear camera
	bool GetTriggerPressed();
	void SetTriggerpressed(bool set);

	void _ToggleCamera();	//change which camera is in use

	void VideoFeed();


private:
	bool GearCamOn;	//true when gear cam is on, false when forward cam is on
	bool TriggerPressed;	//will be true when the trigger is pressed and false when trigger is 0

	int forwardDev;	//device number of the forward camera
	int gearDev;	//device number of the gear camera

	cs::UsbCamera camera1;
	cs::UsbCamera camera2;
	cs::CvSink *cvsink1;
	cs::CvSink *cvsink2;
	cs::VideoSink server;
};

#endif
