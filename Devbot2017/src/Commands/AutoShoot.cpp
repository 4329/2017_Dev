#include "AutoShoot.h"

#include "Delay.h"

#include "StartShooter.h"
#include "StartIndexer.h"

#include "MaintainShooter.h"
#include "MaintainIndex.h"

#include "StopShooter.h"
#include "StopIndexer.h"

AutoShoot::AutoShoot() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::shooter.get());
	Requires(Robot::shooterIndex.get());

	AddSequential(new StartShooter());
	AddParallel(new MaintainShooter());
	AddParallel(new MaintainIndex());
	AddParallel(new StartIndexer());




}
