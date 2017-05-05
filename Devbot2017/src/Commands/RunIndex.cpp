#include "RunIndex.h"
#include "DriverStation.h"


RunIndex::RunIndex(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::shooterIndex.get());
	Requires(Robot::shooter.get());
}

// Called just before this Command runs the first time
void RunIndex::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RunIndex::Execute() {
	Robot::shooterIndex->RunSpeed();

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
bool RunIndex::IsFinished() {
	if (!DriverStation::GetInstance().IsAutonomous()) {	//check if the y button is being held down when it is not auto mode

		if (Robot::oi->getShootButton()->Get()) {	//keep speeding up if y button is pressed
			return false;
		}
		else {
			Robot::shooterIndex->Stop();	//stop speeding up if y button is not pressed
			return true;
		}

	}

	return false;
}

// Called once after isFinished returns true
void RunIndex::End() {
	Robot::shooterIndex->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunIndex::Interrupted() {

}
