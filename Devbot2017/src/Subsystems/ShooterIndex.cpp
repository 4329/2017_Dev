#include "ShooterIndex.h"
#include "../RobotMap.h"

ShooterIndex::ShooterIndex() : Subsystem("Shooter") {
	indexTalon = RobotMap::indexTalon;

	Configuration();
}

void ShooterIndex::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());

}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void ShooterIndex::Configuration() {
	ConfigEncoder();
	SetSpeedMode();

	//SetVoltageMode();

	//indexTalon->SetInverted(false);

	target_SetPoint = 2000.0;
}

void ShooterIndex::Recalc_Fgain() {
	//calculates F
	//(number of Rotations / min) X (1 min / 60 sec) X (1 sec / 10 TvelMeas) X (1024 native units / rotation)
	double Fgain = ( target_SetPoint / 600.0 ) * 4096.0;
	Fgain = (1.0 * 1023.0) / Fgain;

	indexTalon->SelectProfileSlot(0);
	indexTalon->SetF(Fgain);
}

void ShooterIndex::ConfigEncoder() {	//the set up of the encoder
	indexTalon->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	indexTalon->SetSensorDirection(false);
	indexTalon->ConfigEncoderCodesPerRev(4096);

	indexTalon->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	indexTalon->ConfigPeakOutputVoltage(+12.0f, -0.0f);	//may be switched depending on if the
															//sensor direction is true or false
	int AllowCerr = 256;
	indexTalon->SetAllowableClosedLoopErr(AllowCerr);
	indexTalon->SetVoltageRampRate(8.0);
	indexTalon->SetCloseLoopRampRate(12.0);

	Recalc_Fgain();

	indexTalon->SetP(0.5);
	indexTalon->SetI(0);
	indexTalon->SetD(0);
}

void ShooterIndex::SetVoltageMode() {
	indexTalon->SetControlMode(CANSpeedController::kPercentVbus);
	indexTalon->Enable();

	std::cout << "Set index Talon to Voltage mode" << std::endl;
}

void ShooterIndex::RunVoltage() {	//moves talon in voltage mode
	indexTalon->Set(-0.2);	//.2 is a place holder
}

void ShooterIndex::SetSpeedMode() {
	indexTalon->SetControlMode(CANSpeedController::kSpeed);
	indexTalon->Set(0);
	indexTalon->Enable();

	std::cout << "Set index Talon to Speed mode" << std::endl;
}

void ShooterIndex::RunSpeed() {	//moves talon in speed mode
	indexTalon->Set(target_SetPoint);
}

bool ShooterIndex::CorrectRPM() {	//checks if the talon is running faster than the correct speed
	//absolute value is used as talon speed may be negative
	if ( fabs(indexTalon->GetSpeed() ) >= target_SetPoint) {	//needs to work with config system
		return true;
	}
	else {
		return false;
	}
}

void ShooterIndex::Stop() {
	indexTalon->Set(0);
}

double ShooterIndex::GetRPM() {
	return indexTalon->GetSpeed();
}

double ShooterIndex::GetVoltage() {
	return indexTalon->GetOutputVoltage();
}

double ShooterIndex::GetCurrent() {
	return indexTalon->GetOutputCurrent();
}

double ShooterIndex::GetTarget_SetPoint() {
	return target_SetPoint;
}
