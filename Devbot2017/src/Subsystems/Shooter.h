#ifndef SHOOTER_H
#define SHOOTER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include <cmath>
#include "CANTalon.h"


class Shooter: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities

	std::shared_ptr<CANTalon> shooterTalon1;
	std::shared_ptr<CANTalon> shooterTalon2;

public:
	Shooter();
	void InitDefaultCommand();
	void Configuration();

	void Run();
	void Stop();
	bool CorrectRPM();
	void SetSpeedMode();

};

#endif
