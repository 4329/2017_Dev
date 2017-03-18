#include "AutoPrint.h"
#include "../Subsystems/Video.h"

AutoPrint::AutoPrint(std::string autoMode): InstantCommand() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::transmission.get());
	_autoMode = autoMode;
}

// Called just before this Command runs the first time
void AutoPrint::Initialize()
{
	std::cout << "4329 Log: " << GetTime() << ", Auto Mode: " << _autoMode << std::endl;
	Robot::transmission->ShifterOff();	//go to low gear before any auto
}
