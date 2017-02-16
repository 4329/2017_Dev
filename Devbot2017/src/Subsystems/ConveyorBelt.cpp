#include "ConveyorBelt.h"
#include "../RobotMap.h"

ConveyorBelt::ConveyorBelt() : Subsystem("GateKeeper") {
	conveyorTalon = RobotMap::conveyorTalon;

	Configuration();
}

void ConveyorBelt::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());

}


// Put methods for controlling this subsystem
// here. Call these from Commands.

void ConveyorBelt::Configuration() {
	// WRITE CONFIG STUFF HERE
	conveyorTalon->SetInverted(false);
}

void ConveyorBelt::Forward() {
	conveyorTalon->Set(1);
}

void ConveyorBelt::Backward() {
	conveyorTalon->Set(-1);
}

void ConveyorBelt::Stop() {
	conveyorTalon->Set(0);
}

void ConveyorBelt::SetVoltageMode() {
	conveyorTalon->SetControlMode(frc::CANSpeedController::kPercentVbus);
	conveyorTalon->Enable();

	std::cout << "Set Conveyor Talon to Voltage Mode" << std::endl;
}
