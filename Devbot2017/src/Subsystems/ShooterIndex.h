#ifndef SHOOTERINDEX_H
#define SHOOTERINDEX_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <cmath>
#include "CANTalon.h"


class ShooterIndex: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<CANTalon> indexTalon;

public:
	ShooterIndex();
	void InitDefaultCommand();
	void Configuration();
	void ConfigEncoder();

	void SetVoltageMode();
	void ForwardVoltage();
	void BackwardVoltage();

	void SetSpeedMode();
	void ForwardSpeed();
	void BackwardSpeed();
	bool CorrectRPM();

	void Stop();

};

#endif
