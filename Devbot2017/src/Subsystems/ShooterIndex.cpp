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

	target_SetPoint = 2000.0;	//just as a placeholder
}

void ShooterIndex::Set_Fgain() {
	//calculates F
	//(number of Rotations / min) X (1 min / 60 sec) X (1 sec / 10 TvelMeas) X (1024 native units / rotation)
	double Fgain = ( target_SetPoint / 600.0 ) * 4096.0;
	Fgain = (1.0 * 1023.0) / Fgain;

	indexTalon->SelectProfileSlot(0);
	indexTalon->SetF(Fgain);
}

void ShooterIndex::ConfigEncoder() {	//the set up of the encoder
	indexTalon->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);

	bool _sensorReversed = Preferences::GetInstance()->GetBoolean("Indexer::SensorReversed",false);
	indexTalon->SetSensorDirection(_sensorReversed);

	int EncoderCodes = Preferences::GetInstance()->GetInt("Indexer::EncoderPulses",4096);
	indexTalon->ConfigEncoderCodesPerRev(EncoderCodes);

	indexTalon->ConfigNominalOutputVoltage(+0.0f, -0.0f);

	bool _reversed = Preferences::GetInstance()->GetBoolean("Indexer::DirReversed",false);

	//may be switched depending on if the direction is true or false
	if (_reversed) {
		indexTalon->ConfigPeakOutputVoltage(+0.0f, -12.0f);
		direction = -1;
	}
	else {
		indexTalon->ConfigPeakOutputVoltage(+12.0f, -0.0f);
		direction = 1;
	}

	indexTalon->SetVelocityMeasurementPeriod(CANTalon::Period_10Ms);

	int AllowCerr = Preferences::GetInstance()->GetInt("Indexer::AllowableCLerr",256);
	indexTalon->SetAllowableClosedLoopErr(AllowCerr);

	double CLRamp = Preferences::GetInstance()->GetDouble("Indexer::CLRamp",12.0);
	indexTalon->SetCloseLoopRampRate(CLRamp);

	target_SetPoint = Preferences::GetInstance()->GetFloat("Indexer::RPM",0);
	target_SetPoint = direction * target_SetPoint;
	Set_Fgain();

	double Pgain = Preferences::GetInstance()->GetDouble("Indexer::P",5.0);
	indexTalon->SetP(Pgain);

	double Igain = Preferences::GetInstance()->GetDouble("Indexer::I",0.0);
	indexTalon->SetI(Igain);

	double Dgain = Preferences::GetInstance()->GetDouble("Indexer::D",0.0);
	indexTalon->SetD(Dgain);
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
