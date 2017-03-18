#include "FloorGear.h"

FloorGear::FloorGear() : Subsystem("FloorGear") {
	_floorSolenoid = RobotMap::floorSolenoid;

	Configuration();
}

void FloorGear::InitDefaultCommand() {


}

void FloorGear::Configuration() {
	_floorSolenoid->Set(false);
}


void FloorGear::ToggleFloorGear() {
	_floorSolenoid->Set( ! _floorSolenoid->Get() );
}
