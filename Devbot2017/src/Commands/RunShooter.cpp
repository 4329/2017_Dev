#include "RunShooter.h"


RunShooter::RunShooter(): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	Requires(Robot::shooter.get());
}

// Called just before this Command runs the first time
void RunShooter::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void RunShooter::Execute() {
	Robot::shooter->RunSpeed();

	//print out status
	double rpm = Robot::shooter->GetRPM();
	double volt = Robot::shooter->GetVoltage();
	double current = Robot::shooter->GetCurrent();
	double currSetPoint = Robot::shooter->GetCurrent_SetPoint();
	double err = currSetPoint - rpm;
	double now = GetTime();

	std::cout << "4329_LOG:" << now << ":Shooter:SetPoint:" << currSetPoint << ":MeasuredRPM:" << rpm << ":Error:" << err <<
			":OutputVoltage:" << volt << ":OutputCurrent:" << current << std::endl;
}

// Make this return true when this Command no longer needs to run execute()
bool RunShooter::IsFinished() {
    if (Robot::oi->getShootButton()->Get()) {
    	return false;
    }
    else {
    	Robot::shooter->Stop();
    	return true;
    }
}

// Called once after isFinished returns true
void RunShooter::End() {
	Robot::shooter->Stop();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void RunShooter::Interrupted() {

}
