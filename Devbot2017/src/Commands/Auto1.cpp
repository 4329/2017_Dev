#include "Auto1.h"
#include "ToggleGearHolder.h"
#include "Delay.h"
#include "PullGearHolder.h"
#include "PushGearHolder.h"
#include "AutoPrint.h"
#include "MoveStraight_With_G_Ranger.h"
#include "MoveStraight_By_Timeout.h"
#include "Rotate.h"
#include "AlignGear.h"


Auto1::Auto1() {
	//auto for left peg

        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

	// Configurable parameters.
	float  Step1_MoveTimeout = Preferences::GetInstance()->GetFloat("AutoLeftPeg::Step1_MoveTimeout", 2.075);
	float  Step1_Output      = Preferences::GetInstance()->GetFloat("AutoLeftPeg::Step1_Output", 0.6);
	float  Step2_Rotate      = Preferences::GetInstance()->GetFloat("AutoLeftPeg::Step2_Rotate", 56.0);
	float  Step3_MoveTimeout = Preferences::GetInstance()->GetFloat("AutoLeftPeg::Step3_MoveTimeout", 1.25);
	float  Step3_Output      = Preferences::GetInstance()->GetFloat("AutoLeftPeg::Step3_Output", 0.6);
	double Step5_Delay       = Preferences::GetInstance()->GetDouble("AutoLeftPeg::Step5_Delay", 0.5);
	float  Step6_MoveTimeout = Preferences::GetInstance()->GetFloat("AutoLeftPeg::Step6_MoveTimeout", 2.0);
	float  Step6_Output      = Preferences::GetInstance()->GetFloat("AutoLeftPeg::Step6_Output", -0.3);

	//print auto mode and go to low gear
	AddSequential(new AutoPrint("1"));
	AddSequential(new Delay(0.1));

	//1.907
//	AddSequential(new MoveStraight_By_Timeout(2.075, 0.6));	//move forward a bit (robot needs to be at a certain point on the wall
	AddSequential(new MoveStraight_By_Timeout(Step1_MoveTimeout, Step1_Output));	//move forward a bit (robot needs to be at a certain point on the wall

//	AddSequential(new Rotate(56));	//rotate towards the peg
	AddSequential(new Rotate(Step2_Rotate));	//rotate towards the peg
	//AddSequential(new AlignGear());	//center on the peg

	//originally 2.45 seconds at 0.3 voltage
//	AddSequential(new MoveStraight_By_Timeout(1.25, 0.6));	//go to left peg
	AddSequential(new MoveStraight_By_Timeout(Step3_MoveTimeout, Step3_Output));	//go to left peg

	AddSequential(new PushGearHolder());	//put gear on peg

	//AddSequential(new Delay(0.5));	//wait a little bit
	AddSequential(new Delay(Step5_Delay));	//wait a little bit

	//AddSequential(new MoveStraight_By_Timeout(2, -0.3));	//slowly move back towards the wall
	AddSequential(new MoveStraight_By_Timeout(Step6_MoveTimeout, Step6_Output));	//slowly move back towards the wall

	//AddSequential(new Rotate(-60));	//face towards the middle of the field
	//AddSequential(new MoveStraight_By_Timeout(1, 0.5));	//move to the middle of the field
}


