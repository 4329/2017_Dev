#include "GearHolder.h"
#include "../RobotMap.h"


GearHolder::GearHolder() : Subsystem("GearHolder") {
	gearSolenoidExtender = RobotMap::extenderSolenoid;
	gearSolenoidVent = RobotMap::ventSolenoid;

	Configuration();

	SetStart();
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
void GearHolder::ToggleGearHolder() {
	gearSolenoidVent->Set(false);	//just so vent is always off

	gearSolenoidExtender->Set( ! gearSolenoidExtender.get() );	//toggle between off and on
}

void GearHolder::SetStart() {
	gearSolenoidExtender->Set(true);
	gearSolenoidVent->Set(false);
}

void GearHolder::PushGearHolder() {
	gearSolenoidExtender->Set(true);
}

void GearHolder::Vent() {
	gearSolenoidVent->Set(true);
}

void GearHolder::PullGearHolder() {
	gearSolenoidExtender->Set(false);
}
