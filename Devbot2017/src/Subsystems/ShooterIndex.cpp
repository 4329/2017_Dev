#include "ShooterIndex.h"
#include "../RobotMap.h"

ShooterIndex::ShooterIndex() : Subsystem("Shooter") {
	indexTalon = RobotMap::indexTalon;

	Configuration();
}

void ShooterIndex::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());

}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void ShooterIndex::Configuration() {

}


