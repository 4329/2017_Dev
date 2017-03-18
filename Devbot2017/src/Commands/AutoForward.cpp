#include "AutoForward.h"
#include "AutoPrint.h"
#include "MoveStraight_By_Timeout.h"


AutoForward::AutoForward() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

	//robot starts out gear holder facing away from the wall

	//print auto mode and go to low gear
	AddSequential(new AutoPrint("Forward"));

	AddSequential(new MoveStraight_By_Timeout(3, 0.5));
}


