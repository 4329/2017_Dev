#include "GearHolder.h"
#include "../RobotMap.h"


GearHolder::GearHolder() : Subsystem("GearHolder") {
	gearSolenoidExtender = RobotMap::extenderSolenoid;
	gearSolenoidVent = RobotMap::ventSolenoid;
	gearSolenoidFlap = RobotMap::gearSolenoidFlap;

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

void GearHolder::SetStart() {
	gearSolenoidFlap->Set(false);

	gearSolenoidExtender->Set(true);
	gearSolenoidVent->Set(false);
}

void GearHolder::GearFlap_Forward() {
	gearSolenoidFlap->Set(true);
}

void GearHolder::GearFlap_Backward() {
	gearSolenoidFlap->Set(false);
}

void GearHolder::ToggleGearFlap() {
	gearSolenoidFlap->Set( ! gearSolenoidFlap->Get());
}

void GearHolder::ToggleGearHolder() {
	gearSolenoidVent->Set(false);	//just in case

	gearSolenoidExtender->Set( ! gearSolenoidExtender->Get() );	//set solenoid what posistion it isn't in
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
