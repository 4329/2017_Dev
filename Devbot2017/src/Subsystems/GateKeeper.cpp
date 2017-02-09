#include "GateKeeper.h"
#include "../RobotMap.h"

GateKeeper::GateKeeper() : Subsystem("GateKeeper") {
	gateTalon = RobotMap::gateTalon;

	Configuration();
}

void GateKeeper::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());

}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void GateKeeper::Configuration() {
	// WRITE CONFIG STUFF HERE
	gateTalon->SetInverted(false);
}

void GateKeeper::ReceiveFuel() {
	gateTalon->Set(1);
}

void GateKeeper::Stop() {
	gateTalon->Set(0);
}

void GateKeeper::SetVoltageMode() {
	gateTalon->SetControlMode(frc::CANSpeedController::kPercentVbus);
	gateTalon->Enable();
}
