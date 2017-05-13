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

	double target_SetPoint;
	double direction;

	void Set_Fgain();

// Ballard Add
	std::shared_ptr<CANTalon> master;
	std::shared_ptr<CANTalon> follower;

	double Fgain;
	double pgain;
	double igain;
	double dgain;
	int EncPulses;
	int AllowCLerr;
	double VoltRamp;

	double _currentSetPoint;
	double _targetSetPoint;
	bool _reversed;
	bool _sensorReversed;
	bool _running;

	double direction;
	void Recalc();

// Ballard Add End


public:
	//shooter should be moving forward( set to positive values ) when not inverted

	Shooter();
	void InitDefaultCommand();
	void Configuration();
	void ConfigEncoder();

	void RunSpeed();
	void RunVoltage();
	void Stop();
	bool CorrectRPM();
	void SetSpeedMode();
	void SetVoltageMode();

	double GetTarget_SetPoint();

	double GetRPM();
	double GetVoltage();
	double GetCurrent();

// Ballard Add
	void Config();

	double CurrentSetPoint();
	void   SetCurrentSetPoint(double value);

	void Run();
	void Start();
	void MDBStop();
	void ReverseDirection();
	void ReverseSensor();

	void Finish();
	bool IsRunning();

	void SetP(double value);
	void SetI(double value);
	void SetD(double value);
	// Ballard Add End
};

#endif
