// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef GEARHOLDER_H
#define GEARHOLDER_H
#include "Commands/Subsystem.h"
#include "WPILib.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class GearHolder: public Subsystem {
public:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	GearHolder();
	void InitDefaultCommand();
	void Configuration();

	void SetStart();

	//for getting gear from feed
	void GearFlap_Forward();
	void GearFlap_Backward();
	void ToggleGearFlap();

	//for putting gear on peg and climbing
	void ToggleGearHolder();
	void PushGearHolder();
	void Vent_On();
	void Vent_Off();
	void PullGearHolder();

	bool GetVentValue();


private:
	//for climbing and putting gear on peg
	std::shared_ptr<Solenoid> gearSolenoidExtender;
	std::shared_ptr<Solenoid> gearSolenoidVent;

	//for getting gears
	std::shared_ptr<Solenoid> gearSolenoidFlap;
};

#endif
