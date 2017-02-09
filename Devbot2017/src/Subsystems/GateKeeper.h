#ifndef GATEKEEPER_H
#define GATEKEEPER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "CANTalon.h"


class GateKeeper: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<CANTalon> gateTalon;

public:
	GateKeeper();
	void InitDefaultCommand();

	void Configuration();
	void ReceiveFuel();
	void Stop();
	void SetVoltageMode();
};

#endif
