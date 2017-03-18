#include "AutoSimple.h"
#include "Rotate.h"
#include "AutoPrint.h"
#include "MoveStraight_With_G_Ranger.h"


AutoSimple::AutoSimple() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

	//print auto mode and go to low gear
	AddSequential(new AutoPrint("simple"));

	//robot starts out intake facing away from the wall
	AddSequential(new MoveStraight_With_G_Ranger(true, 230.0), 5);	//move past line stop after 5 seconds
}


