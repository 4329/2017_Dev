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
	ConfigEncoder();
	SetSpeedMode();
	//SetVoltageMode();

	//shooterTalon1->SetInverted(false);
	//shooterTalon2->SetInverted(false);
	target_SetPoint = 3500.0;
	current_SetPoint = target_SetPoint;
}

void Shooter::Recalc_Fgain() {
	//calculates F
	//(number of Rotations / min) X (1 min / 60 sec) X (1 sec / 10 TvelMeas) X (1024 native units / rotation)
	double Fgain = ( current_SetPoint / 600.0 ) * 4096.0;
	Fgain = (1.0 * 1023.0) / Fgain;

	shooterTalon1->SelectProfileSlot(0);
	shooterTalon1->SetF(Fgain);
}

void Shooter::ConfigEncoder() {
	shooterTalon1->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	shooterTalon1->SetSensorDirection(false);
	shooterTalon1->ConfigEncoderCodesPerRev(4096);

	shooterTalon1->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	shooterTalon1->ConfigPeakOutputVoltage(+12.0f, -0.0f);	//may be switched depending on if the
															//sensor direction is true or false
	int allowCerr = 256;
	shooterTalon1->SetAllowableClosedLoopErr(allowCerr);
	shooterTalon1->SetVoltageRampRate(8.0);

	shooterTalon1->SetP(0.9);
	shooterTalon1->SetI(0.1);
	shooterTalon1->SetD(0.1);

	shooterTalon1->SetVelocityMeasurementPeriod(CANTalon::Period_10Ms);
	shooterTalon1->SetAllowableClosedLoopErr(100);
	shooterTalon1->SetVoltageRampRate(8.0);
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
	shooterTalon1->Set(current_SetPoint);
}

void Shooter::RunVoltage() {
	shooterTalon1->Set(0.75);
}

void Shooter::Stop() {
	shooterTalon1->Set(0);
}

bool Shooter::CorrectRPM() {
	if ( fabs(GetRPM() ) >= target_SetPoint) {	//needs to work with config system
		std::cout << "reached the correct speed" << std::endl;
		return true;
	}
	else {
		std::cout << "Speed: " << fabs(GetRPM()) << std::endl;
		return false;
	}
}

double Shooter::GetCurrent_SetPoint() {
	return current_SetPoint;
}

void Shooter::SetCurrent_SetPoint(double value) {
	current_SetPoint = value;
	Recalc_Fgain();
}

double Shooter::GetRPM()
{
	double speed = shooterTalon1->GetSpeed();
	return speed;
}

double Shooter::GetVoltage()
{
	double voltage = shooterTalon1->GetOutputVoltage();
	return voltage;
}

double Shooter::GetCurrent()
{
	double current = shooterTalon1->GetOutputCurrent();
	return current;
}
