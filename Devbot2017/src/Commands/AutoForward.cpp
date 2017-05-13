#include "AutoForward.h"
#include "AutoPrint.h"
#include "MoveStraight_By_Timeout.h"


AutoForward::AutoForward() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

	//robot starts out gear holder facing away from the wall

	//print auto mode and go to low gear
	AddSequential(new AutoPrint("Forward"));

	// Configurable parameters.
	float  Step1_MoveTimeout = Preferences::GetInstance()->GetFloat("AutoForward::Step1_MoveTimeout", 3.0);
	float  Step1_Output      = Preferences::GetInstance()->GetFloat("AutoForward::Step1_Output", 0.5);

	//AddSequential(new MoveStraight_By_Timeout(3, 0.5));
	AddSequential(new MoveStraight_By_Timeout(Step1_MoveTimeout, Step1_Output));
}


