#include "Rotate.h"

Rotate::Rotate(float Angle): Command() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::driveTrain.get());

    correctYaw = 0.0;
	targetAngle = Angle;
	output = 0.225;
	error = 4;
}

// Called just before this Command runs the first time
void Rotate::Initialize() {
	std::cout << "now rotating " << targetAngle << std::endl;
	Robot::driveTrain->SetVoltageMode();
	Robot::imu->Reset(); //reset yaw angle to 0
}

// Called repeatedly when this Command is scheduled to run
void Rotate::Execute() {
	std::cout << "Yaw: " << Robot::imu->GetYaw() << std::endl;

	float sensorYaw = Robot::imu->GetYaw();

	//get the correct yaw (value between 0 and 180)
	if (sensorYaw < 0) {
		correctYaw = 360 + sensorYaw;
	}
	else {
		correctYaw = sensorYaw;
	}

	//change direction just in case robot goes over
	if (fabs(targetAngle) < fabs(Robot::imu->GetYaw())) {
		output = -fabs(output);	//output is always negative(opposite direction that it started with)
	}
	else {
		output = fabs(output);	//output is always positive(same direction that it started with)
	}

	//move robot left for negative angles and right for positive angles
	if (targetAngle > 0) {
		Robot::driveTrain->DirectDrive(-output, output);
	}
	else {
		Robot::driveTrain->DirectDrive(output, -output);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool Rotate::IsFinished() {
	float correctAngle;

	//set the correct angle
	if (targetAngle < 0) {
		correctAngle = 360 + (targetAngle - error);
	}
	else {
		correctAngle = targetAngle + error;
	}

	//if the difference between the yaw and angle is small enough command will stop
	if (fabs(correctAngle - correctYaw) < error) {
		std::cout << "done rotating " << std::endl;
		return true;
	}
	else {
		return false;
	}
}

// Called once after isFinished returns true
void Rotate::End() {
	Robot::driveTrain->StopMotors();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void Rotate::Interrupted() {

}
