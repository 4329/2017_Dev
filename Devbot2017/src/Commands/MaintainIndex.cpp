#include "MaintainIndex.h"


MaintainIndex::MaintainIndex(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::shooterIndex.get());
}


// Called just before this Command runs the first time
void MaintainIndex::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void MaintainIndex::Execute() {
	Robot::shooterIndex->Run();
	//print out status
	double rpm = Robot::shooterIndex->GetRPM();
	double volt = Robot::shooterIndex->GetVoltage();
	double current = Robot::shooterIndex->GetCurrent();
	double currSetPoint = Robot::shooterIndex->GetTarget_SetPoint();
	double err = currSetPoint - rpm;
	double now = GetTime();
	std::cout << "4329_LOG:" << now << ":Indexer:SetPoint:" << currSetPoint << ":MeasuredRPM:" << rpm << ":Error:" << err <<
			":OutputVoltage:" << volt << ":OutputCurrent:" << current << std::endl;
}

// Make this return true when this Command no longer needs to run execute()
bool MaintainIndex::IsFinished() {
    return Robot::shooterIndex->IsRunning();
}

// Called once after isFinished returns true
void MaintainIndex::End() {
	Robot::shooterIndex->MDBStop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MaintainIndex::Interrupted() {

}
