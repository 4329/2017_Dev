#include "Shoot.h"
#include "ReceiveFuel.h"
#include "RunShooter.h"
#include "SpeedUpShooter.h"


Shoot::Shoot() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::shooter.get());
	Requires(Robot::gateKeeper.get());

	//run shooter until it is at the appropriate speed
	AddSequential(new SpeedUpShooter());	//possibly add timeout?

	//take in fuel and continuously run the shooter to shoot the fuel
	AddParallel(new ReceiveFuel());
	AddParallel(new RunShooter());
}
