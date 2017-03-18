#include "Auto3.h"
#include "ToggleGearHolder.h"
#include "Delay.h"
#include "PullGearHolder.h"
#include "PushGearHolder.h"
#include "AutoPrint.h"
#include "MoveStraight_With_G_Ranger.h"
#include "MoveStraight_By_Timeout.h"
#include "Rotate.h"
#include "AlignGear.h"


Auto3::Auto3() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

	//print auto mode and go to low gear
	AddSequential(new AutoPrint("3"));

	AddSequential(new MoveStraight_By_Timeout(5, 0.3));	//move forward a bit (robot needs to be at a certain point on the wall
	AddSequential(new Rotate(-60));	//rotate towards the peg
	//AddSequential(new AlignGear());	//center on the peg

	AddSequential(new MoveStraight_By_Timeout(2.5, 0.3));	//go to right peg
	AddSequential(new PushGearHolder());	//put gear on peg
	AddSequential(new Delay(0.5));	//wait a little bit
	AddSequential(new MoveStraight_By_Timeout(2, -0.3));	//slowly move back towards the wall
	AddSequential(new PullGearHolder());	//Retract the gear holder

	//AddSequential(new Rotate(60));	//face towards the middle of the field
	//AddSequential(new MoveStraight_By_Timeout(1, 0.5));	//move to the middle of the field

}


