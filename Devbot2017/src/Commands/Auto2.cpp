#include "Auto2.h"
#include "ToggleGearHolder.h"
#include "Delay.h"
#include "PullGearHolder.h"
#include "PushGearHolder.h"
#include "AutoPrint.h"
#include "MoveStraight_With_G_Ranger.h"
#include "MoveStraight_By_Timeout.h"

//279.4 cm from wall to airship
//53.34 cm from back side of robot to shooter ultrasonic sensor
//final distance is 221.1 cm (226.1 - 5)

//this currently uses the gear ultrasonic sensor
Auto2::Auto2() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());
	Requires(Robot::gearholder.get());

	//print auto mode and go to low gear
	AddSequential(new AutoPrint("auto 2"));

	//AddSequential(new MoveStraight_With_G_Ranger(false, 25));	//move until 25 cm away from airship

	//move a little bit so the peg is in the robot
	AddSequential(new MoveStraight_By_Timeout(Robot::config->returnFloat("auto2::timeout"), Robot::config->returnFloat("auto2::output")));
	AddSequential(new PushGearHolder());	//put gear on peg
	AddSequential(new Delay(Robot::config->returnDouble("auto2::gear_place_delay")));	//wait a little bit
	AddSequential(new MoveStraight_By_Timeout(2, -0.3));	//slowly move back towards the wall
}

