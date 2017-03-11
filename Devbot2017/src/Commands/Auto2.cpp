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
//the robot gets to the airship in about 2.7 seconds at 0.5 voltage
//so the robot moves 83.7 cm / second at 0.5 voltage (8.37 cm per 10 milliseconds)

//this currently uses the gear ultrasonic sensor
Auto2::Auto2() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());
	Requires(Robot::gearholder.get());

	AddSequential(new AutoPrint("auto 2"));

	AddSequential(new MoveStraight_With_G_Ranger(false, 25));	//move until 25 cm away from airship
	AddSequential(new MoveStraight_By_Timeout(0.5, 0.25));	//move a little bit so the peg is in the robot
	AddSequential(new PushGearHolder());	//put gear on peg
	AddSequential(new Delay(1));	//wait a little bit
	AddSequential(new MoveStraight_By_Timeout(2, -0.3));	//slowly move back towards the wall
	AddSequential(new PullGearHolder());	//Retract the gear holder
}

