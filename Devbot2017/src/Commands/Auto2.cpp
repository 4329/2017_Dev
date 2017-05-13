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
	//auto for middle peg

        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());
	Requires(Robot::gearholder.get());

	// Configurable parameters.
	float  Step1_MoveTimeout = Preferences::GetInstance()->GetFloat("AutoMiddlePeg::Step1_MoveTimeout", 2.0);
	float  Step1_Output      = Preferences::GetInstance()->GetFloat("AutoMiddlePeg::Step1_Output", 0.55);
	float  Step2_MoveTimeout = Preferences::GetInstance()->GetFloat("AutoMiddlePeg::Step2_MoveTimeout", 0.5);
	float  Step2_Output      = Preferences::GetInstance()->GetFloat("AutoMiddlePeg::Step2_Output", 0.3);
	double Step4_Delay       = Preferences::GetInstance()->GetDouble("AutoMiddlePeg::Step4_Delay", 1);
	float  Step5_MoveTimeout = Preferences::GetInstance()->GetFloat("AutoMiddlePeg::Step5_MoveTimeout", 2.0);
	float  Step5_Output      = Preferences::GetInstance()->GetFloat("AutoMiddlePeg::Step5_Output", -0.3);



	//print auto mode and go to low gear
	AddSequential(new AutoPrint("auto 2"));
	AddSequential(new Delay(0.1));

	//AddSequential(new MoveStraight_With_G_Ranger(false, 25));	//move until 25 cm away from airship
	//AddSequential(new MoveStraight_By_Timeout(2, 0.55));	//move a little bit so the peg is in the robot
	AddSequential(new MoveStraight_By_Timeout(Step1_MoveTimeout, Step1_Output));	//move a little bit so the peg is in the robot


	//AddSequential(new MoveStraight_By_Timeout(0.5, 0.3));	//move a little bit so the peg is in the robot
	AddSequential(new MoveStraight_By_Timeout(Step2_MoveTimeout, Step2_Output));	//move a little bit so the peg is in the robot

	AddSequential(new PushGearHolder());	//put gear on peg

	//AddSequential(new Delay(1));	//wait a little bit
	AddSequential(new Delay(Step4_Delay));	//wait a little bit

	//AddSequential(new MoveStraight_By_Timeout(2, -0.3));	//slowly move back towards the wall
	AddSequential(new MoveStraight_By_Timeout(Step5_MoveTimeout, Step5_Output));	//slowly move back towards the wall
}

