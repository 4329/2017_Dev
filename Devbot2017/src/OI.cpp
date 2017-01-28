// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "OI.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "SmartDashboard/SmartDashboard.h"
#include "Commands/AutonomousCommand.h"
#include "Commands/TeleopDrive.h"
#include "Commands/ToggleShift.h"
#include "Commands/Fuel_Outtake.h"
#include "Commands/Fuel_Intake.h"

// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES

OI::OI() {
    // Process operator interface input here.
    robotOperator.reset(new XboxController(1));
    robotDriver.reset(new XboxController(0));
    
    shift.reset(new JoystickButton(robotDriver.get(), Xbox_Button::A));
    outtake.reset( new  JoystickButton( robotOperator.get() , Xbox_Button::B)  );

    outtake->WhenPressed(new Fuel_Outtake());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    shift->WhenPressed(new ToggleShift());

    // SmartDashboard Buttons
    SmartDashboard::PutData("ToggleShift", new ToggleShift());
    SmartDashboard::PutData("Autonomous Command", new AutonomousCommand());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
}

std::shared_ptr<XboxController> OI::getRobotDriver() {
   return robotDriver;
}

std::shared_ptr<XboxController> OI::getRobotOperator() {
   return robotOperator;
}


float OI::GetAxisValue(std::shared_ptr<XboxController> controller, int axis) {
	float value;

	switch (axis) {
	case Xbox_Axis::Xbox_Axis_Left_X:
		value = No_DeadZone_Value(controller->GetRawAxis(axis), LeftX_min);
		break;
	case Xbox_Axis::Xbox_Axis_Left_Y:
		value = -1 * No_DeadZone_Value(controller->GetRawAxis(axis), LeftY_min);	//y axis is inverted
		break;
	case Xbox_Axis::Xbox_Axis_Left_Trigger:
		value = No_DeadZone_Value(controller->GetRawAxis(axis), LeftTrigger_min);
		break;
	case Xbox_Axis::Xbox_Axis_Right_Trigger:
		value = No_DeadZone_Value(controller->GetRawAxis(axis), Righttrigger_min);
		break;
	case Xbox_Axis::Xbox_Axis_Right_X:
		value = No_DeadZone_Value(controller->GetRawAxis(axis), RightX_min);
		break;
	case Xbox_Axis::Xbox_Axis_Right_Y:
		value = -1 * No_DeadZone_Value(controller->GetRawAxis(axis), RightY_min); //y axis is inverted
		break;
	case Xbox_Axis::Xbox_Axis_DPad_X:
		value = controller->GetRawAxis(axis);
		break;
	case Xbox_Axis::Xbox_Axis_DPad_Y:
		value = controller->GetRawAxis(axis);
		break;
	default:
		std::cerr << "Unhandled axis: " << __LINE__ << " value " << axis << std::endl;
		value = 0;
	}


	return value;
}

float OI::No_DeadZone_Value(float value, float deadZone) {	//this should work with triggers as well
	if ( (value < deadZone) and (value >= 0) ) {
		return 0;
	}
	else if ( (value > -deadZone) and (value <= 0) ) {
		return 0;
	}
	else {
		return value;
	}
}
