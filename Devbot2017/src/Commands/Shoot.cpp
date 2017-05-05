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

	AddSequential(new SpeedUpShooter(), 5.0);	//will stop speeding up the shooter when 5 seconds have passed
	AddParallel(new RunIndex());
	AddParallel(new RunShooter());
}
