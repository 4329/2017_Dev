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

	double target_SetPoint;
	double direction;

	void Set_Fgain();

public:
	//index should be moving backwards(set to negative values) when not inverted

	//set up stuff
	ShooterIndex();
	void InitDefaultCommand();
	void Configuration();
	void ConfigEncoder();

	//used when motor doesn't have a encoder
	void SetVoltageMode();
	void RunVoltage();

	//when motor does have an encoder
	void SetSpeedMode();
	void RunSpeed();
	bool CorrectRPM();

	void Stop();

	double GetRPM();
	double GetVoltage();
	double GetCurrent();

	double GetTarget_SetPoint();
};

#endif
