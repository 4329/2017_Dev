#include "AutoSimple.h"
#include "MoveStraight_With_S_Ranger.h"
#include "Rotate.h"
#include "AutoPrint.h"


AutoSimple::AutoSimple() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

	//robot starts out facing towards the wall
	AddSequential(new AutoPrint("Simple"));
	AddSequential(new MoveStraight_With_S_Ranger(true, 230.0));	//move past line
}


