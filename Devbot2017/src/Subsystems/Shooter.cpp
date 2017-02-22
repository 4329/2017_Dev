#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("Shooter") {
	shooterTalon1 = RobotMap::shooterTalon1;
	shooterTalon2 = RobotMap::shooterTalon2;

	Configuration();
}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());

}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::Configuration() {
	//ConfigEncoder();
	//SetSpeedMode();
	SetVoltageMode();
	//shooterTalon1->SetInverted(false);
	//shooterTalon2->SetInverted(false);
}

void Shooter::ConfigEncoder() {
	shooterTalon1->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);
	shooterTalon1->SetSensorDirection(false);
	shooterTalon1->ConfigEncoderCodesPerRev(1024);

	shooterTalon1->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	shooterTalon1->ConfigPeakOutputVoltage(+12.0f, -0.0f);	//may be switched depending on if the
															//sensor direction is true or false
	//calculates F
	//(number of Rotations / min) X (1 min / 60 sec) X (1 sec / 10 TvelMeas) X (1024 native units / rotation)
	double Fgain = ( 10000 / 600 ) * 1024;	//10000 is a placeholder
	Fgain = (0.5 * 1023) / Fgain;	//the 0.5 is a placeholder

	shooterTalon1->SelectProfileSlot(0);
	shooterTalon1->SetF(Fgain);
	shooterTalon1->SetP(0);
	shooterTalon1->SetI(0);
	shooterTalon1->SetD(0);
}

void Shooter::SetSpeedMode() {	//needs to be called before shooter is used
	//change mode
	shooterTalon1->SetControlMode(frc::CANSpeedController::kSpeed);
	shooterTalon2->SetControlMode(frc::CANSpeedController::kFollower);

	//set which master talons the slave talons follow
	shooterTalon2->Set(7);

	shooterTalon1->Set(0);	//motor won't move

	//enable after changing the control mode
	shooterTalon1->Enable();
	shooterTalon2->Enable();
}

void Shooter::SetVoltageMode() {
	//change mode
	shooterTalon1->SetControlMode(frc::CANSpeedController::kPercentVbus);
	shooterTalon2->SetControlMode(frc::CANSpeedController::kFollower);

	//set which master talons the slave talons follow
	shooterTalon2->Set(7);

	shooterTalon1->Set(0);	//motor won't move

	//enable after changing the control mode
	shooterTalon1->Enable();
	shooterTalon2->Enable();
}

void Shooter::RunSpeed() {
	shooterTalon1->Set(10000);
}

void Shooter::RunVoltage() {
	shooterTalon1->Set(0.75);
}

void Shooter::Stop() {
	shooterTalon1->Set(0);
}

bool Shooter::CorrectRPM() {
	if ( fabs(shooterTalon1->GetSpeed() ) >= 10000) {	//needs to work with config system
		return true;
	}
	else {
		return false;
	}
}
