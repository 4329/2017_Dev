#ifndef VIDEO_H
#define VIDEO_H

#include "WPILib.h"
#include <Thread>
#include <CameraServer.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/core/types.hpp>

typedef struct
{
	int SelectedCamera;
	int changeCount;
} cameraControl;

class Video {
public:
	Video();

    void SetCC(cameraControl *cc);
    bool Init();
    void Run();
    void End();
    void Configure();
    void ChangeCam(int cam);

private:
	cs::UsbCamera camera1;
	cs::UsbCamera camera2;
	cs::CvSink *cvsink1;
	cs::CvSink *cvsink2;
	cs::VideoSink server;
	int myChangeCount;
	cameraControl *myCC;
	int myCam;

};

#endif
