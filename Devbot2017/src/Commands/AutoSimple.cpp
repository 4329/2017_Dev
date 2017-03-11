#include "AutoSimple.h"
#include "Rotate.h"
#include "AutoPrint.h"
#include "MoveStraight_With_G_Ranger.h"


AutoSimple::AutoSimple() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

	//robot starts out intake facing away from the wall
	AddSequential(new AutoPrint("Simple"));
	AddSequential(new MoveStraight_With_G_Ranger(true, 230.0), 5);	//move past line stop after 5 seconds
}


