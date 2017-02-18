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
	//ConfigEncoder();
	//SetSpeedMode();

	SetVoltageMode();
}

void ShooterIndex::ConfigEncoder() {
	indexTalon->SetFeedbackDevice(CANTalon::FeedbackDevice::CtreMagEncoder_Absolute);
	indexTalon->SetSensorDirection(false);
	indexTalon->ConfigEncoderCodesPerRev(1024);

	indexTalon->ConfigNominalOutputVoltage(+0.0f, -0.0f);
	indexTalon->ConfigPeakOutputVoltage(+12.0f, -0.0f);	//may be switched depending on if the
															//sensor direction is true or false
	//calculates F
	//(number of Rotations / min) X (1 min / 60 sec) X (1 sec / 10 TvelMeas) X (1024 native units / rotation)
	double Fgain = ( 10000 / 600 ) * 1024;	//10000 is a placeholder
	Fgain = (0.5 * 1023) / Fgain;	//the 0.5 is a placeholder

	indexTalon->SelectProfileSlot(0);
	indexTalon->SetF(Fgain);
	indexTalon->SetP(0);
	indexTalon->SetI(0);
	indexTalon->SetD(0);
}

void ShooterIndex::SetVoltageMode() {
	indexTalon->SetControlMode(CANSpeedController::kPercentVbus);
	indexTalon->Enable();

	std::cout << "Set index Talon to Voltage mode" << std::endl;
}

void ShooterIndex::ForwardVoltage() {
	indexTalon->Set(1);	//1 is a place holder
}

void ShooterIndex::BackwardVoltage() {
	indexTalon->Set(-1); //1 is a place holder
}

void ShooterIndex::SetSpeedMode() {
	indexTalon->SetControlMode(CANSpeedController::kSpeed);
	indexTalon->Set(0);
	indexTalon->Enable();

	std::cout << "Set index Talon to Speed mode" << std::endl;
}

void ShooterIndex::ForwardSpeed() {
	indexTalon->Set(2000); //2000 is a place holder
	std::cout << "index: " << indexTalon->GetOutputVoltage() << std::endl;
}

void ShooterIndex::BackwardSpeed() {
	indexTalon->Set(-2000); //2000 is a place holder
	std::cout << "index: " << indexTalon->GetOutputVoltage() << std::endl;
}

bool ShooterIndex::CorrectRPM() {
	if ( fabs(indexTalon->GetSpeed() ) >= 2000) {	//needs to work with config system
		return true;
	}
	else {
		return false;
	}
}

void ShooterIndex::Stop() {
	indexTalon->Set(0);
}
