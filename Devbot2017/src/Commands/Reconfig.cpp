// RobotBuilder Version: 2.0
//
// This file was generated by RobotBuilder. It contains sections of
// code that are automatically generated and assigned by robotbuilder.
// These sections will be updated in the future when you export to
// C++ from RobotBuilder. Do not put any code or make any change in
// the blocks indicating autogenerated code or it will be lost on an
// update. Deleting the comments indicating the section will prevent
// it from being updated in the future.


#include "Reconfig.h"

// BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

Reconfig::Reconfig(): InstantCommand() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
    // BEGIN AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
	Requires(Robot::shooterIndex.get());
	Requires(Robot::shooter.get());
    // END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=REQUIRES
}
// END AUTOGENERATED CODE, SOURCE=ROBOTBUILDER ID=CONSTRUCTOR

// Called once when this command runs
void Reconfig::Initialize() {
	Robot::shooterIndex->ConfigEncoder();
	Robot::shooter->ConfigEncoder();

	double now = GetTime();

	float  AutoLeftPeg_Step1_MoveTimeout          = Preferences::GetInstance()->GetFloat("AutoLeftPeg::Step1_MoveTimeout", 2.075);
	float  AutoLeftPeg_Step1_Output               = Preferences::GetInstance()->GetFloat("AutoLeftPeg::Step1_Output", 0.6);
	float  AutoLeftPeg_Step2_Rotate               = Preferences::GetInstance()->GetFloat("AutoLeftPeg::Step2_Rotate", 56.0);
	float  AutoLeftPeg_Step3_MoveTimeout          = Preferences::GetInstance()->GetFloat("AutoLeftPeg::Step3_MoveTimeout", 1.25);
	float  AutoLeftPeg_Step3_Output               = Preferences::GetInstance()->GetFloat("AutoLeftPeg::Step3_Output", 0.6);
	double AutoLeftPeg_Step5_Delay                = Preferences::GetInstance()->GetDouble("AutoLeftPeg::Step5_Delay", 0.5);
	float  AutoLeftPeg_Step6_MoveTimeout          = Preferences::GetInstance()->GetFloat("AutoLeftPeg::Step6_MoveTimeout", 2.0);
	float  AutoLeftPeg_Step6_Output               = Preferences::GetInstance()->GetFloat("AutoLeftPeg::Step6_Output", -0.3);

	std::cout << "4329_LOG:" << now << ":Reconfigure:" << ":AutoLeftPeg:S1_MoveTOut:" << AutoLeftPeg_Step1_MoveTimeout <<
			":S1_Output:" << AutoLeftPeg_Step1_Output << ":S2_Rotate:" << AutoLeftPeg_Step2_Rotate <<
			":S3_MoveTOut:" << AutoLeftPeg_Step3_MoveTimeout << ":S3_Output:" << AutoLeftPeg_Step3_Output <<
			":S5_Delay:" << AutoLeftPeg_Step5_Delay << ":S6_MoveTOut:" << AutoLeftPeg_Step6_MoveTimeout <<
			":S6_Output:" << AutoLeftPeg_Step6_Output << std::endl;

	float  AutoMiddlePeg_Step1_MoveTimeout        = Preferences::GetInstance()->GetFloat("AutoMiddlePeg::Step1_MoveTimeout", 2.0);
	float  AutoMiddlePeg_Step1_Output             = Preferences::GetInstance()->GetFloat("AutoMiddlePeg::Step1_Output", 0.55);
	float  AutoMiddlePeg_Step2_MoveTimeout        = Preferences::GetInstance()->GetFloat("AutoMiddlePeg::Step2_MoveTimeout", 0.5);
	float  AutoMiddlePeg_Step2_Output             = Preferences::GetInstance()->GetFloat("AutoMiddlePeg::Step2_Output", 0.3);
	double AutoMiddlePeg_Step4_Delay              = Preferences::GetInstance()->GetDouble("AutoMiddlePeg::Step4_Delay", 1);
	float  AutoMiddlePeg_Step5_MoveTimeout        = Preferences::GetInstance()->GetFloat("AutoMiddlePeg::Step5_MoveTimeout", 2.0);
	float  AutoMiddlePeg_Step5_Output             = Preferences::GetInstance()->GetFloat("AutoMiddlePeg::Step5_Output", -0.3);

	std::cout << "4329_LOG:" << now << ":Reconfigure:" << ":AutoMiddlePeg:S1_MoveTOut:" << AutoMiddlePeg_Step1_MoveTimeout <<
			":S1_Output:" << AutoMiddlePeg_Step1_Output << ":S2_MoveTOut:" << AutoMiddlePeg_Step2_MoveTimeout <<
			":S2_Output:" << AutoMiddlePeg_Step2_Output << ":S4_Delay:" << AutoMiddlePeg_Step4_Delay <<
			":S5_MoveTOut:" << AutoMiddlePeg_Step5_MoveTimeout << ":S5_Output:" << AutoMiddlePeg_Step5_Output << std::endl;


	float  AutoRightPeg_Step1_MoveTimeout         = Preferences::GetInstance()->GetFloat("AutoRightPeg::Step1_MoveTimeout", 2.075);
	float  AutoRightPeg_Step1_Output              = Preferences::GetInstance()->GetFloat("AutoRightPeg::Step1_Output", 0.6);
	float  AutoRightPeg_Step2_Rotate              = Preferences::GetInstance()->GetFloat("AutoRightPeg::Step2_Rotate", -56.0);
	float  AutoRightPeg_Step3_MoveTimeout         = Preferences::GetInstance()->GetFloat("AutoRightPeg::Step3_MoveTimeout", 1.25);
	float  AutoRightPeg_Step3_Output              = Preferences::GetInstance()->GetFloat("AutoRightPeg::Step3_Output", 0.6);
	double AutoRightPeg_Step5_Delay               = Preferences::GetInstance()->GetDouble("AutoRightPeg::Step5_Delay", 0.5);
	float  AutoRightPeg_Step6_MoveTimeout         = Preferences::GetInstance()->GetFloat("AutoRightPeg::Step6_MoveTimeout", 2.0);
	float  AutoRightPeg_Step6_Output              = Preferences::GetInstance()->GetFloat("AutoRightPeg::Step6_Output", -0.3);

	std::cout << "4329_LOG:" << now << ":Reconfigure:" << ":AutoRightPeg:S1_MoveTOut:" << AutoRightPeg_Step1_MoveTimeout <<
			":S1_Output:" << AutoRightPeg_Step1_Output << ":S2_Rotate:" << AutoRightPeg_Step2_Rotate <<
			":S3_MoveTOut:" << AutoRightPeg_Step3_MoveTimeout << ":S3_Output:" << AutoRightPeg_Step3_Output <<
			":S5_Delay:" << AutoRightPeg_Step5_Delay << ":S6_MoveTOut:" << AutoRightPeg_Step6_MoveTimeout <<
			":S6_Output:" << AutoRightPeg_Step6_Output << std::endl;


	float  AutoForward_Step1_MoveTimeout          = Preferences::GetInstance()->GetFloat("AutoForward::Step1_MoveTimeout", 3.0);
	float  AutoForward_Step1_Output               = Preferences::GetInstance()->GetFloat("AutoForward::Step1_Output", 0.5);

	std::cout << "4329_LOG:" << now << ":Reconfigure:" << ":AutoForward:S1_MoveTOut:" << AutoForward_Step1_MoveTimeout <<
			":S1_Output:" << AutoForward_Step1_Output << std::endl;


	bool   AutoMovePastLineSensor_Step1_GoForward = Preferences::GetInstance()->GetBoolean("AutoMovePastLineSensor::Step1_GoForward", true);
	double AutoMovePastLineSensor_Step1_DistCM    = Preferences::GetInstance()->GetDouble("AutoMovePastLineSensor::Step1_DistCM", 230.0);
	double AutoMovePastLineSensor_Step1_TimeOut   = Preferences::GetInstance()->GetDouble("AutoMovePastLineSensor::Step1_TimeOut", 5.0);

	std::cout << "4329_LOG:" << now << ":Reconfigure:" << ":AutoMovePastLineWSensor:S1_GoForward:" << AutoMovePastLineSensor_Step1_GoForward <<
			":S1_DistCM:" << AutoMovePastLineSensor_Step1_DistCM << ":S1_TimeOut:" << AutoMovePastLineSensor_Step1_TimeOut << std::endl;

	std::cout << "4329_LOG:" << now << ":Reconfigured" << std::endl;
}
