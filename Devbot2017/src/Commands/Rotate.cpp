#include "Rotate.h"

Rotate::Rotate(float Angle): Command() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::driveTrain.get());

    correctYaw = 0.0;
	targetAngle = Angle;
	output = 0.2;
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

	float direction = 1;
	float sensorYaw = Robot::imu->GetYaw();

	//get the correct yaw (value between 0 and 180) and set the direction (right or left)
	if (sensorYaw < 0) {
		correctYaw = 360 + sensorYaw;
		direction = -1.0;
	}
	else {
		correctYaw = sensorYaw;
		direction = 1.0;
	}

	//move robot
	Robot::driveTrain->DirectDrive(output*direction, output*direction);
}

// Make this return true when this Command no longer needs to run execute()
bool Rotate::IsFinished() {
	float correctAngle;

	//set the correct angle
	if (targetAngle < 0) {
								//360 + (-180 - 4) = 176, it should be 184 [360 + (-180 + 4) = 4]
		correctAngle = 360 + (targetAngle + error);
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
