// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "XboxController.h"
#include <iostream>

class OI {
private:
	//buttons
	// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<JoystickButton> shift;
	// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=DECLARATIONS
	std::shared_ptr<JoystickButton> outtake;
	std::shared_ptr<JoystickButton> intake;


	//controllers
	std::shared_ptr<XboxController> robotOperator;
	std::shared_ptr<XboxController> robotDriver;

	//dead zones
		float LeftX_min 		= 0.1;
		float LeftY_min 		= 0.1;
		float LeftTrigger_min 	= 0.1;
		float Righttrigger_min 	= 0.1;
		float RightX_min 		= 0.1;
		float RightY_min 		= 0.1;

public:

	//button and axis number values
	enum Xbox_Button
	{
		A 				= 1,
		B 				= 2,
		X 				= 3,
		Y 				= 4,
		Left_Bumper 	= 5,
		Right_Bumper 	= 6,
		Back 			= 7,
		Start 			= 8,
		Left_Stick 		= 9,
		Right_Stick 	= 10
	};

	enum Xbox_Axis
	{
		Xbox_Axis_Left_X 			= 0,	// left: 1, right -1
		Xbox_Axis_Left_Y 			= 1,	// upwards: -1, downwards: 1 ( GetAxisValue() makes this upwards: 1, downwards -1 )
		Xbox_Axis_Left_Trigger 		= 2,	// not pressed: 0, pressed: 1
		Xbox_Axis_Right_Trigger		= 3,	// not pressed: 0, pressed: 1
		Xbox_Axis_Right_X 			= 4,	// left: 1, right -1
		Xbox_Axis_Right_Y 			= 5,	// upwards: -1, downwards: 1 ( GetAxisValue() makes this upwards: 1, downwards -1 )
		Xbox_Axis_DPad_X 			= 6,
		Xbox_Axis_DPad_Y 			= 7
	};



	OI();

	std::shared_ptr<XboxController> getRobotDriver();
	std::shared_ptr<XboxController> getRobotOperator();

	float GetAxisValue(std::shared_ptr<XboxController> controller, int axis);	//gets the axis value of the specified button (with dead zones)
	float No_DeadZone_Value(float value, float deadZone);	//returns a value that, which will be 0 if it is in the deadzone value
															//Ex. if dead zone value is 0.1
															//-1 will be -1, 0.5 will be 0, -0.5 will be 0, etc
	float No_DeadZone_TriggerValue(float value, float deadZone);
};

#endif