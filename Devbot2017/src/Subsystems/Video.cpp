#include "Video.h"



Video::Video() {
	camera1 = frc::CameraServer::GetInstance()->StartAutomaticCapture(0);
	camera2 = frc::CameraServer::GetInstance()->StartAutomaticCapture(1);
	server = frc::CameraServer::GetInstance()->GetServer();
	  // dummy sinks to keep camera connections open
	camera1.SetResolution(320, 240);
	camera2.SetResolution(320, 240);
	camera1.SetBrightness(60);
	camera2.SetBrightness(60);
	camera1.SetFPS(15);
	camera2.SetFPS(15);
	cvsink1 = new cs::CvSink("GearCam");
	cvsink1->SetSource(camera1);
	cvsink1->SetEnabled(true);
	cvsink2 = new cs::CvSink("ShooterCam");
	cvsink2->SetSource(camera2);
	cvsink2->SetEnabled(true);
	myCC = NULL;
	myChangeCount = 0;
	myCam = 0;
	server.SetSource(camera1);
}

void Video::SetCC(cameraControl *cc)
{
	myCC = cc;
	myChangeCount = cc->changeCount;
}

bool Video::Init()
{
	return true;
}

void Video::Run()
{
	while (true)
	{
		Configure();
	}
}

void Video::End()
{

}

void Video::Configure()
{
	if (myCC->changeCount != myChangeCount)
	{
		ChangeCam(myCC->SelectedCamera);
	}

	myChangeCount = myCC->changeCount;
}

void Video::ChangeCam(int cam)
{
	if (myCam != cam)
	{
		if (cam == 0)
		{
			std::cout << "Selecting Camera 1" << std::endl;
			server.SetSource(camera1);
		} else
		{
			std::cout << "Selecting Camera 2" << std::endl;
			server.SetSource(camera2);
		}
	}
}

