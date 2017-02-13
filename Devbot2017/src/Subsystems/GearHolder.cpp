#include "GearHolder.h"
#include "../RobotMap.h"


GearHolder::GearHolder() : Subsystem("GearHolder") {
	gearSolenoid1 = RobotMap::gearSolenoid1;
	gearSolenoid2 = RobotMap::gearSolenoid2;

	Configuration();
}

void GearHolder::InitDefaultCommand() {
    // Set the default command for a subsystem here.
}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void GearHolder::Configuration() {
//put config stuff here
}

//change functions later
void GearHolder::PushGearHolder() {
	gearSolenoid1->Set(true);
	gearSolenoid2->Set(true);
}

void GearHolder::PullGearHolder() {
	gearSolenoid1->Set(false);
	gearSolenoid2->Set(false);
}
