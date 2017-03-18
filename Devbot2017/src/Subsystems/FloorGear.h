#ifndef FLOORGEAR_H
#define FLOORGEAR_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../RobotMap.h"

class FloorGear : public Subsystem {
public:
	FloorGear();

	void InitDefaultCommand();
	void Configuration();

	void ToggleFloorGear();



private:
	std::shared_ptr<frc::Solenoid> _floorSolenoid;
};


#endif
