#include "Auto2.h"
#include "MoveStraight_With_S_Ranger.h"
#include "Rotate.h"
#include "ToggleGearHolder.h"
#include "Shoot.h"

//218.44 cm from robot to airship

Auto2::Auto2() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());
	Requires(Robot::gearholder.get());
	Requires(Robot::shooter.get());

	AddSequential(new MoveStraight_With_S_Ranger(true, 109.22));

}

