#include "AutoSimple.h"
#include "MoveStraight_With_S_Ranger.h"
#include "Rotate.h"


AutoSimple::AutoSimple() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

	//robot starts out facing towards the wall
	AddSequential(new MoveStraight_With_S_Ranger(true, 690.0));	//move backwards near the middle of the field
}


