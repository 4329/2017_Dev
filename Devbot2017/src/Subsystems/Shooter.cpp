#include "Commands/RunShooter.h"
#include "Shooter.h"
#include "../RobotMap.h"

Shooter::Shooter() : Subsystem("Shooter") {
	shooterTalon1 = RobotMap::shooterTalon1;
	shooterTalon2 = RobotMap::shooterTalon2;

//	Configuration();

    master   = RobotMap::shooterTalon1;
    follower = RobotMap::shooterTalon2;

    Fgain = 0.0;
    _currentSetPoint = 0.0;
    _running = false;
    direction = 1;

    _targetSetPoint = Preferences::GetInstance()->GetFloat("Shooter::RPM",0);
    _reversed = Preferences::GetInstance()->GetBoolean("Shooter::DirReversed",false);
    _sensorReversed = Preferences::GetInstance()->GetBoolean("Shooter::SensorReversed",false);

    pgain = Preferences::GetInstance()->GetDouble("Shooter::P",0.0);
    igain = Preferences::GetInstance()->GetDouble("Shooter::I",0.0);
    dgain = Preferences::GetInstance()->GetDouble("Shooter::D",0.0);

	EncPulses = Preferences::GetInstance()->GetInt("Shooter::EncoderPulses",4096);
	AllowCLerr = Preferences::GetInstance()->GetInt("Shooter::AllowableCLerr",5);
	VoltRamp = Preferences::GetInstance()->GetDouble("Shooter::VoltRamp",12.0);

	SmartDashboard::PutBoolean("Shooter Running",_running);

}

void Shooter::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());
	   SetDefaultCommand(new RunShooter());
}

// Put methods for controlling this subsystem
// here. Call these from Commands.

void Shooter::Configuration() {
	ConfigEncoder();
	SetSpeedMode();
	//SetVoltageMode();

	//shooterTalon1->SetInverted(false);
	//shooterTalon2->SetInverted(false);

	target_SetPoint = 3500.0;	//just as a placeholder
	direction = 1;
}

void Shooter::Set_Fgain() {
	//calculates F
	//(number of Rotations / min) X (1 min / 60 sec) X (1 sec / 10 TvelMeas) X (1024 native units / rotation)
	double Fgain = ( target_SetPoint / 600.0 ) * 4096.0;
	Fgain = (1.0 * 1023.0) / Fgain;

	shooterTalon1->SelectProfileSlot(0);
	shooterTalon1->SetF(Fgain);

	SmartDashboard::PutNumber("Shooter FGain",Fgain);
}

void Shooter::ConfigEncoder() {
	shooterTalon1->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);

	bool _sensorReversed = Preferences::GetInstance()->GetBoolean("Shooter::SensorReversed",false);
	shooterTalon1->SetSensorDirection(_sensorReversed);

	int EncoderCodes = Preferences::GetInstance()->GetInt("Shooter::EncoderCodesperRev", 4096);
	shooterTalon1->ConfigEncoderCodesPerRev(EncoderCodes);

	shooterTalon1->ConfigNominalOutputVoltage(+0.0f, -0.0f);

	bool _reversed = Preferences::GetInstance()->GetBoolean("Shooter::DirReversed",false);

	//may be switched depending on if the direction is true or false
	if (_reversed)	{
		shooterTalon1->ConfigPeakOutputVoltage(+0.0f, -12.0f);
		direction = -1;
	}
	else {
		shooterTalon1->ConfigPeakOutputVoltage(+12.0f, -0.0f);
		direction = 1;
	}

	target_SetPoint = Preferences::GetInstance()->GetFloat("Shooter::RPM",0);
	target_SetPoint = direction * target_SetPoint;
	Set_Fgain();

	int allowCerr = Preferences::GetInstance()->GetInt("Shooter::AllowableCLerr",256);;
	shooterTalon1->SetAllowableClosedLoopErr(allowCerr);

	double RampRate = Preferences::GetInstance()->GetDouble("Shooter::VoltRamp",8.0);
	shooterTalon1->SetVoltageRampRate(RampRate);

	Set_Fgain();

	double Pgain = Preferences::GetInstance()->GetDouble("Shooter::P",5.0);
	shooterTalon1->SetP(Pgain);

	double Igain = Preferences::GetInstance()->GetDouble("Shooter::I",0.0);
	shooterTalon1->SetI(Igain);

	double Dgain = Preferences::GetInstance()->GetDouble("Shooter::D",0.0);
	shooterTalon1->SetD(Dgain);

	//shooterTalon1->SetVelocityMeasurementPeriod(CANTalon::Period_10Ms);
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
	shooterTalon1->Set(target_SetPoint);
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

double Shooter::GetTarget_SetPoint() {
	return target_SetPoint;
}

double Shooter::GetRPM()
{
	double speed = shooterTalon1->GetSpeed();
	SmartDashboard::PutNumber("Shooter Measured RPM",speed);
	return speed;
}

double Shooter::GetVoltage()
{
	double voltage = shooterTalon1->GetOutputVoltage();
	SmartDashboard::PutNumber("Shooter Output Voltage",voltage);
	return voltage;
}

double Shooter::GetCurrent()
{
	double current = shooterTalon1->GetOutputCurrent();
	SmartDashboard::PutNumber("Shooter Output Current", current);
	return current;
}

void Shooter::Config()
{
	master->SetControlMode(frc::CANSpeedController::kSpeed);
	follower->SetControlMode(frc::CANSpeedController::kFollower);

	master->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Relative);
	_sensorReversed = Preferences::GetInstance()->GetBoolean("Shooter::SensorReversed",false);
	master->SetSensorDirection(_sensorReversed);

	EncPulses = Preferences::GetInstance()->GetInt("Shooter::EncoderPulses",4096);
	master->ConfigEncoderCodesPerRev(EncPulses);

	master->ConfigNominalOutputVoltage(+0.0f, -0.0f);

	_reversed = Preferences::GetInstance()->GetBoolean("Shooter::DirReversed",false);

	if (_reversed)
	{
		master->ConfigPeakOutputVoltage(+0.0f, -12.0f);
		direction = -1;

	} else
	{
		master->ConfigPeakOutputVoltage(+12.0f, -0.0f);
		direction = 1;
	}

//	master->SetVelocityMeasurementPeriod(CANTalon::Period_10Ms);

	AllowCLerr = Preferences::GetInstance()->GetInt("Shooter::AllowableCLerr",10);
	master->SetAllowableClosedLoopErr(AllowCLerr);

	VoltRamp = Preferences::GetInstance()->GetDouble("Shooter::VoltRamp",12.0);
	master->SetVoltageRampRate(VoltRamp);

	_targetSetPoint = Preferences::GetInstance()->GetFloat("Shooter::RPM",0);
	_currentSetPoint = direction * _targetSetPoint;
	Recalc();

	master->SelectProfileSlot(0);
	master->SetF(Fgain);

	pgain = Preferences::GetInstance()->GetDouble("Shooter::P",0.05);
	master->SetP(pgain);

	igain = Preferences::GetInstance()->GetDouble("Shooter::I",0.0);
	master->SetI(igain);

	dgain = Preferences::GetInstance()->GetDouble("Shooter::D",0.0);
	master->SetD(dgain);

	follower->Set(7);

	double now = GetTime();
	std::cout << "4329_LOG:" << now << ":Shooter:Config:_sensorReversed:" << _sensorReversed <<
			":EncPulses:" << EncPulses << ":_reversed:" << _reversed <<
			":AllowCLerr:" << AllowCLerr << ":VoltRamp:" << VoltRamp <<
			":pgain:" << pgain << ":igain:" << igain << ":dgain:" << dgain << ":CalFgain:" << Fgain <<
			":SetPoint:" << _targetSetPoint << std::endl;

}

double Shooter::CurrentSetPoint()
{
	return _currentSetPoint;
}

void Shooter::Recalc()
{
	//calculates F
	//(number of Rotations / min) X (1 min / 60 sec) X (1 sec / 10 TvelMeas) X (1024 native units / rotation)
	Fgain = ( _currentSetPoint / 600.0 ) * 4096.0;
	Fgain = (1.0 * 1023.0) / Fgain;

	master->SelectProfileSlot(0);
	master->SetF(Fgain);

	SmartDashboard::PutNumber("Shooter FGain",Fgain);

}

void Shooter::SetCurrentSetPoint(double value)
{
	_currentSetPoint = value;
	Recalc();
}

void Shooter::Run()
{
	if (_running)
	{
		master->Set(_currentSetPoint);
		SmartDashboard::PutNumber("Shooter SetPoint RPM",_currentSetPoint);
	}
}

void Shooter::Start()
{
	if (!_running)
	{
		Config();
		master->Enable();
		follower->Enable();
		_targetSetPoint = Preferences::GetInstance()->GetFloat("Shooter::RPM",0);
		_currentSetPoint = direction * _targetSetPoint;
		_running = true;
		SmartDashboard::PutBoolean("Shooter Running",_running);
	}
}

void Shooter::MDBStop()
{
	_running = false;
	_currentSetPoint = 0.0;
	master->Set(_currentSetPoint);
	master->Disable();
	SmartDashboard::PutBoolean("Shooter Running",_running);
}

void Shooter::ReverseDirection()
{
	_reversed = !_reversed;
	direction = direction * -1;
	_targetSetPoint = _targetSetPoint * direction;
	Preferences::GetInstance()->PutFloat("Shooter::RPM",_targetSetPoint);
	Config();
}

void Shooter::ReverseSensor()
{
	_sensorReversed = !_sensorReversed;
	Config();
}

void Shooter::SetP(double value)
{
	pgain = value;
	master->SetP(pgain);
}

void Shooter::SetI(double value)
{
	igain = value;
	master->SetI(igain);
}

void Shooter::SetD(double value)
{
    dgain = value;
	master->SetD(dgain);
}

void Shooter::Finish()
{
	_running = false;
}

bool Shooter::IsRunning()
{
	return _running;
}
