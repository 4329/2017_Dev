#include "MoveStraight_By_Timeout.h"

MoveStraight_By_Timeout::MoveStraight_By_Timeout(float timeout, float output): Command() {
        // Use requires() here to declare subsystem dependencies
	Requires(Robot::driveTrain.get());
	_timeout = timeout;
	_output = output;
}

// Called just before this Command runs the first time
void MoveStraight_By_Timeout::Initialize() {
	Robot::imu->ZeroYaw();	//resets the yaw before the command
	std::cout << "4329 Log: " << GetTime() << ", moving straight by timeout" << std::endl;
	SetTimeout(_timeout);
}

// Called repeatedly when this Command is scheduled to run
void MoveStraight_By_Timeout::Execute() {
	Robot::driveTrain->HeadingDrive(_output);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveStraight_By_Timeout::IsFinished() {
	return IsTimedOut();
}

// Called once after isFinished returns true
void MoveStraight_By_Timeout::End() {
	std::cout << "4329 Log: " << GetTime() << ", done moving straight by timeout" << std::endl;
	Robot::imu->ZeroYaw();	//resets the yaw before the next usage
	Robot::driveTrain->StopMotors();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveStraight_By_Timeout::Interrupted()
{

}
