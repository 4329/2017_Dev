#include "ShooterIndex.h"
#include "../RobotMap.h"

ShooterIndex::ShooterIndex() : Subsystem("Shooter") {
	indexTalon = RobotMap::indexTalon;

//	Configuration();

	ndxTalon = RobotMap::indexTalon;
    Fgain = 0.0;
    _currentSetPoint = 0.0;
    _running = false;
    direction = 1;

    _targetSetPoint = Preferences::GetInstance()->GetFloat("Indexer::RPM",500);
    _reversed = Preferences::GetInstance()->GetBoolean("Indexer::DirReversed",false);
    _sensorReversed = Preferences::GetInstance()->GetBoolean("Indexer::SensorReversed",false);

    pgain = Preferences::GetInstance()->GetDouble("Indexer::P",0.05);
    igain = Preferences::GetInstance()->GetDouble("Indexer::I",0.0);
    dgain = Preferences::GetInstance()->GetDouble("Indexer::D",0.0);

	EncPulses = Preferences::GetInstance()->GetInt("Indexer::EncoderPulses",4096);
	AllowCLerr = Preferences::GetInstance()->GetInt("Indexer::AllowableCLerr",10);
	CLRamp = Preferences::GetInstance()->GetDouble("Indexer::CLRamp",12.0);

	SmartDashboard::PutBoolean("Indexer Running",_running);
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

double ShooterIndex::GetTarget_SetPoint() {
	return target_SetPoint;
}


// Ballard Add
void ShooterIndex::Config()
{
	ndxTalon->SetControlMode(frc::CANSpeedController::kSpeed);
	ndxTalon->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);

	_sensorReversed = Preferences::GetInstance()->GetBoolean("Indexer::SensorReversed",false);
	ndxTalon->SetSensorDirection(_sensorReversed);

	EncPulses = Preferences::GetInstance()->GetInt("Indexer::EncoderPulses",4096);
	ndxTalon->ConfigEncoderCodesPerRev(EncPulses);

	ndxTalon->ConfigNominalOutputVoltage(+0.0f, -0.0f);

	_reversed = Preferences::GetInstance()->GetBoolean("Indexer::DirReversed",false);

	if (_reversed)
	{
		ndxTalon->ConfigPeakOutputVoltage(+0.0f, -12.0f);
		direction = -1;
	} else
	{
		ndxTalon->ConfigPeakOutputVoltage(+12.0f, -0.0f);
		direction = 1;
	}

	//ndxTalon->SetVelocityMeasurementPeriod(CANTalon::Period_10Ms);

	AllowCLerr = Preferences::GetInstance()->GetInt("Indexer::AllowableCLerr",10);
	ndxTalon->SetAllowableClosedLoopErr(AllowCLerr);

	CLRamp = Preferences::GetInstance()->GetDouble("Indexer::CLRamp",12.0);
	ndxTalon->SetCloseLoopRampRate(CLRamp);

	_targetSetPoint = Preferences::GetInstance()->GetFloat("Indexer::RPM",0);
	_currentSetPoint = direction * _targetSetPoint;
	Recalc();

	ndxTalon->SelectProfileSlot(0);
	ndxTalon->SetF(Fgain);

	pgain = Preferences::GetInstance()->GetDouble("Indexer::P",0.05);
	ndxTalon->SetP(pgain);

	igain = Preferences::GetInstance()->GetDouble("Indexer::I",0.0);
	ndxTalon->SetI(igain);

	dgain = Preferences::GetInstance()->GetDouble("Indexer::D",0.0);
	ndxTalon->SetD(dgain);

	double now = GetTime();
	std::cout << "4329_LOG:" << now << ":Indexer:Config:_sensorReversed:" << _sensorReversed <<
			":EncPulses:" << EncPulses << ":_reversed:" << _reversed <<
			":AllowCLerr:" << AllowCLerr << ":CLRamp:" << CLRamp <<
			":pgain:" << pgain << ":igain:" << igain << ":dgain:" << dgain << ":CalFgain:" << Fgain <<
			":SetPoint:" << _targetSetPoint << std::endl;
}

double ShooterIndex::CurrentSetPoint()
{
	return _currentSetPoint;
}

void ShooterIndex::Recalc()
{
	//calculates F
	//(number of Rotations / min) X (1 min / 60 sec) X (1 sec / 10 TvelMeas) X (1024 native units / rotation)
	//Fgain = ( _currentSetPoint / 600 ) * 4096;
	Fgain = ( _currentSetPoint / 600 ) * EncPulses;
	Fgain = (1.0 * 1023) / Fgain;

	ndxTalon->SelectProfileSlot(0);
	ndxTalon->SetF(Fgain);

}

void ShooterIndex::SetCurrentSetPoint(double value)
{
	_currentSetPoint = value;
	Recalc();
}

double ShooterIndex::GetRPM()
{
	double speed = ndxTalon->GetSpeed();
	SmartDashboard::PutNumber("Indexer Measured RPM",speed);
	return speed;
}

double ShooterIndex::GetVoltage()
{
	double voltage = ndxTalon->GetOutputVoltage();
	SmartDashboard::PutNumber("Indexer Output Voltage",voltage);
	return voltage;
}

double ShooterIndex::GetCurrent()
{
	double current = ndxTalon->GetOutputCurrent();
	SmartDashboard::PutNumber("Indexer Output Current", current);
	return current;
}

void ShooterIndex::Run()
{
	if (_running)
	{
		ndxTalon->Set(_currentSetPoint);
		SmartDashboard::PutNumber("Indexer SetPoint RPM",_currentSetPoint);
	}
}

void ShooterIndex::Start()
{
	if (!_running)
	{
		Config();
		ndxTalon->Enable();
		_targetSetPoint = Preferences::GetInstance()->GetFloat("Indexer::RPM",0);
		_currentSetPoint = direction * _targetSetPoint;
		_running = true;
		SmartDashboard::PutBoolean("Indexer Running",_running);
	}
}

void ShooterIndex::MDBStop()
{
	_running = false;
	_currentSetPoint = 0.0;
	ndxTalon->Set(_currentSetPoint);
	ndxTalon->Disable();
	SmartDashboard::PutBoolean("Indexer Running",_running);
}

void ShooterIndex::ReverseDirection()
{
	_reversed = !_reversed;
	Config();
}

void ShooterIndex::ReverseSensor()
{
	_sensorReversed = !_sensorReversed;
	Config();
}

void ShooterIndex::SetP(double value)
{
	pgain = value;
	ndxTalon->SetP(pgain);
}

void ShooterIndex::SetI(double value)
{
	igain = value;
	ndxTalon->SetI(igain);
}

void ShooterIndex::SetD(double value)
{
    dgain = value;
    ndxTalon->SetD(dgain);
}

void ShooterIndex::Finish()
{
	_running = false;
}

bool ShooterIndex::IsRunning()
{
	return _running;
}


