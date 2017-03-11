#include "Auto1.h"
#include "AutoPrint.h"


Auto1::Auto1() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

	AddSequential(new AutoPrint("1"));
}


