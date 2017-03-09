#include "Auto2.h"
#include "MoveStraight_With_S_Ranger.h"
#include "Rotate.h"
#include "ToggleGearHolder.h"
#include "Shoot.h"
#include "AlignGear.h"
#include "AlignShoot.h"
#include "Delay.h"

//218.44 cm from robot to airship

Auto2::Auto2() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());
	Requires(Robot::gearholder.get());
	Requires(Robot::shooter.get());

	AddSequential(new MoveStraight_With_S_Ranger(true, 145.0));	//145 is about 2/3 to the airship
	AddSequential(new AlignGear());	//face the gear
	AddSequential(new MoveStraight_With_S_Ranger(true, 10.0));	//get right in front of peg
	AddSequential(new ToggleGearHolder());	//place gear
	AddSequential(new Delay(1));	//wait until gear is placed on peg

	//move back and pull the gear holder at the same time
	AddParallel(new ToggleGearHolder());
	AddSequential(new MoveStraight_With_S_Ranger(false, 109.0));	//109 is about 1/2 to the wall

	AddSequential(new Rotate(70));	//face somewhat close to the boiler
	AddSequential(new AlignShoot());	//face boiler
	AddSequential(new MoveStraight_With_S_Ranger(true, 30.0));	//go to boiler (30 cm is just a place holder)
	AddSequential(new AlignShoot());	//face boiler again

	AddParallel(new Shoot());	//start shooting until end of auto
}

