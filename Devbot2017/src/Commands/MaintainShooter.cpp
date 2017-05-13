#include "MaintainShooter.h"


MaintainShooter::MaintainShooter(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::shooter.get());
}


// Called just before this Command runs the first time
void MaintainShooter::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void MaintainShooter::Execute() {
	Robot::shooter->Run();
	//print out status
	double rpm = Robot::shooter->GetRPM();
	double volt = Robot::shooter->GetVoltage();
	double current = Robot::shooter->GetCurrent();
	double currSetPoint = Robot::shooter->GetTarget_SetPoint();
	double err = currSetPoint - rpm;
	double now = GetTime();

	std::cout << "4329_LOG:" << now << ":Shooter:SetPoint:" << currSetPoint << ":MeasuredRPM:" << rpm << ":Error:" << err <<
			":OutputVoltage:" << volt << ":OutputCurrent:" << current << std::endl;
}

// Make this return true when this Command no longer needs to run execute()
bool MaintainShooter::IsFinished() {
	return Robot::shooter->IsRunning();
}

// Called once after isFinished returns true
void MaintainShooter::End() {
	Robot::shooter->MDBStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MaintainShooter::Interrupted() {

}
