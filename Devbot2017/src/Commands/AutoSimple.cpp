#include "AutoSimple.h"
#include "MoveStraight_With_S_Ranger.h"
#include "Rotate.h"


AutoSimple::AutoSimple() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

	//robot starts out facing towards the wall
	AddSequential(new MoveStraight_With_S_Ranger(false, 700));	//move backwards near the middle of the field
	AddSequential(new Rotate(180));	//face in the opposite direction
}


