#include "Shoot.h"

#include "Delay.h"

#include "SpeedUpShooter.h"
#include "SpeedUpIndex.h"

#include "ShooterTurn.h"
#include "ShooterForward.h"

#include "RunIndex.h"
#include "RunShooter.h"


Shoot::Shoot() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::shooter.get());
	Requires(Robot::shooterIndex.get());

	//run shooter until it is at the appropriate speed
	//AddSequential(new SpeedUpShooter());	//possibly add timeout?						//AddParallel(new SpeedUpShooter());
																						//AddParallel(new SpeedUpIndex());

																						//AddSequential(new ShooterTurn());
																						//AddSequential(new ShooterForward());

	//take in fuel and continuously run the shooter to shoot the fuel
	AddSequential(new SpeedUpShooter());
	AddParallel(new RunIndex());

}
