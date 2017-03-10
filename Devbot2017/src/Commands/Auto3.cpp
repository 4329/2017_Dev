#include "Auto3.h"
#include "AutoPrint.h"


Auto3::Auto3() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

	AddSequential(new AutoPrint("3"));

}


