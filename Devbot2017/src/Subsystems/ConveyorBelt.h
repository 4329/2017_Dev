#ifndef CONVEYORBELT_H
#define CONVEYORBELT_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"


class ConveyorBelt: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> conveyorTalon;

public:
	ConveyorBelt();
	void InitDefaultCommand();

	void Configuration();
	void Forward();
	void Backward();
	void Stop();
	void SetVoltageMode();
};

#endif
