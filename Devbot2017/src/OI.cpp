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
#include "Commands/TeleopDrive.h"
#include "Commands/ToggleShift.h"
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=INCLUDES
#include "Commands/AutoSimple.h"
#include "Commands/Auto1.h"
#include "Commands/Auto2.h"
#include "Commands/Auto3.h"
#include "Commands/MoveStraight_By_Timeout.h"

#include "Commands/AlignGear.h"
#include "Commands/AlignShoot.h"
#include "Commands/ToggleCamera.h"

#include "Commands/FuelIntake.h"
#include "Commands/ToggleGearHolder.h"
#include "Commands/Shoot.h"
#include "Commands/Climb.h"
#include "Commands/Vent_On.h"
#include "Commands/Vent_Off.h"
#include "Commands/ClimbSequence.h"
#include "Commands/PrintBlockData.h"
#include "Commands/OpenFlap.h"
#include "Commands/PushGearHolder.h"
#include "Commands/PullGearHolder.h"
#include "Commands/ToggleGearFlap.h"
#include "Commands/ConveyorBackward.h"
#include "Commands/ToggleSpeed.h"
#include "Commands/Rotate.h"
#include "Commands/MoveStraight.h"

#include <cmath> //for dead zones
#include "Commands/MoveStraight_With_G_Ranger.h"

OI::OI() {
    // Process operator interface input here.
    robotOperator.reset(new XboxController(1));
    robotDriver.reset(new XboxController(0));
    
    //reset shared pointer buttons
    shift.reset(new JoystickButton(robotDriver.get(), Xbox_Button::Right_Bumper));
    toggleHighSpeed.reset(new JoystickButton(robotDriver.get(), Xbox_Button::Left_Bumper));
    ToggleGearHolder_B.reset(new JoystickButton(robotOperator.get(), Xbox_Button::Right_Bumper));
    shoot.reset(new JoystickButton(robotOperator.get(), Xbox_Button::X));
    RobotClimb.reset(new JoystickButton(robotOperator.get(), Xbox_Button::Y));
    Flap.reset(new JoystickButton(robotOperator.get(), Xbox_Button::B));	//held for now
    ConveyorBackward_B.reset(new JoystickButton(robotOperator.get(), Xbox_Button::Left_Bumper));
    //toggleCamera.reset(new JoystickButton(robotDriver.get(), Xbox_Button::A));

    //Specify which commands to call when button is pressed, released, etc
    //toggleCamera->WhenPressed(new ToggleCamera());
    //ConveyorBackward_B->WhenPressed(new ConveyorBackward());
    Flap->WhenPressed(new OpenFlap());	//actually while held
    ToggleGearHolder_B->WhenPressed(new ToggleGearHolder());
    shoot->WhenPressed(new Shoot());	//actually while held
    RobotClimb->WhenPressed(new ClimbSequence());	//actually while held
    toggleHighSpeed->WhenPressed(new ToggleSpeed());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    shift->WhenPressed(new ToggleShift());


    // SmartDashboard Buttons
    SmartDashboard::PutData("ToggleShift", new ToggleShift());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTORS
    SmartDashboard::PutData("AutoSimple", new AutoSimple());
    SmartDashboard::PutData("Auto1", new Auto1());
    SmartDashboard::PutData("Auto2", new Auto2());
    SmartDashboard::PutData("Auto3", new Auto3());
    SmartDashboard::PutData("AutoSimple2", new MoveStraight_By_Timeout(3, 0.5));

    SmartDashboard::PutData("AlignGear", new AlignGear());
    SmartDashboard::PutData("AlignShoot", new AlignShoot());
    SmartDashboard::PutData("MoveForward_With_G_Ranger", new MoveStraight_With_G_Ranger(true, 200.0));
    SmartDashboard::PutData("MoveBackward_With_G_Ranger", new MoveStraight_With_G_Ranger(false, 200.0));
    SmartDashboard::PutData("ToggleCamera", new ToggleCamera());

    SmartDashboard::PutData("PrintBlockData", new PrintBlockData());
    SmartDashboard::PutData("Vent_On", new Vent_On());
    SmartDashboard::PutData("Vent_Off", new Vent_Off());
    SmartDashboard::PutData("PushGearHolder", new PushGearHolder());
    SmartDashboard::PutData("PullGearHolder", new PullGearHolder());
    SmartDashboard::PutData("ToggleGearFlap", new ToggleGearFlap());
    SmartDashboard::PutData("ToggleGearHolder", new ToggleGearHolder());

    //Positive rotates left, negative rotates right
    SmartDashboard::PutData("Rotate 90", new Rotate(90));
    SmartDashboard::PutData("Rotate 180", new Rotate(180));

    SmartDashboard::PutData("Rotate -90", new Rotate(-90));
    SmartDashboard::PutData("Rotate -180", new Rotate(-180));

    SmartDashboard::PutData("Forward 3ft", new MoveStraight(3));

    SmartDashboard::PutBoolean("HighSpeed", Robot::driveTrain->GetHighSpeed());
    SmartDashboard::PutBoolean("HighGear", Robot::transmission->GetHighGear());
}

std::shared_ptr<XboxController> OI::getRobotDriver() {
   return robotDriver;
}

std::shared_ptr<XboxController> OI::getRobotOperator() {
   return robotOperator;
}

std::shared_ptr<JoystickButton> OI::getClimbButton() {
   return RobotClimb;
}

std::shared_ptr<JoystickButton> OI::getShootButton() {
   return shoot;
}

std::shared_ptr<JoystickButton> OI::getFlapButton() {
   return Flap;
}

std::shared_ptr<JoystickButton> OI::getConveyorBackwardButton() {
   return ConveyorBackward_B;
}

float OI::GetAxisValue(std::shared_ptr<XboxController> controller, int axis) {
	float value;

	switch (axis) {
	case Xbox_Axis::Xbox_Axis_Left_X:
		value = No_DeadZone_Value(controller->GetRawAxis(axis), LeftX_min);
		if (value == 0.0) { value = 0.0; }	//so value isn't -0, but is 0
		break;

	case Xbox_Axis::Xbox_Axis_Left_Y:
		value = No_DeadZone_Value(controller->GetRawAxis(axis), LeftY_min);	//y axis shouldn't be inverted
																			//as the arcade drive code is tailored to
																			//the y axis not being inverted
		if (value == 0.0) { value = 0.0; }
		break;

	case Xbox_Axis::Xbox_Axis_Left_Trigger:
		value = No_DeadZone_Value(controller->GetRawAxis(axis), LeftTrigger_min);
		break;

	case Xbox_Axis::Xbox_Axis_Right_Trigger:
		value = No_DeadZone_Value(controller->GetRawAxis(axis), Righttrigger_min);
		break;

	case Xbox_Axis::Xbox_Axis_Right_X:
		value = No_DeadZone_Value(controller->GetRawAxis(axis), RightX_min);
		if (value == 0.0) { value = 0.0; }
		break;

	case Xbox_Axis::Xbox_Axis_Right_Y:
		value = No_DeadZone_Value(controller->GetRawAxis(axis), RightY_min);	//y axis shouldn't be inverted
		if (value == 0.0) { value = 0.0; }
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

float OI::No_DeadZone_Value(float value, float deadZone) {	//works with all axes
	if ( fabs(value) < deadZone ) {
		return 0.0;
	}
	else {
		return value;
	}
}
