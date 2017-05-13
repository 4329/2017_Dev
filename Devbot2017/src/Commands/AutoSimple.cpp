#include "AutoSimple.h"
#include "Rotate.h"
#include "AutoPrint.h"
#include "MoveStraight_With_G_Ranger.h"


AutoSimple::AutoSimple() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::driveTrain.get());

	// Configurable parameters.
	bool   Step1_GoForward = Preferences::GetInstance()->GetBoolean("AutoMovePastLineSensor::Step1_GoForward", true);
	double Step1_DistCM    = Preferences::GetInstance()->GetDouble("AutoMovePastLineSensor::Step1_DistCM", 230.0);
	double Step1_TimeOut   = Preferences::GetInstance()->GetDouble("AutoMovePastLineSensor::Step1_TimeOut", 5.0);

	//print auto mode and go to low gear
	AddSequential(new AutoPrint("simple"));

	//robot starts out intake facing away from the wall
	//AddSequential(new MoveStraight_With_G_Ranger(true, 230.0), 5);	//move past line stop after 5 seconds
	AddSequential(new MoveStraight_With_G_Ranger(Step1_GoForward, Step1_DistCM), Step1_TimeOut);	//move past line stop after 5 seconds
}


