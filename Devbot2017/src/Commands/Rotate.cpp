#include "Rotate.h"

Rotate::Rotate(float Angle): Command() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::driveTrain.get());

    correctAngle = Angle;	//just for set up
	targetAngle = Angle;
	output = 0.25;
	direction = 1;	//just for set up
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

	float correctYaw;
	float sensorYaw = Robot::imu->GetYaw();

	if (sensorYaw < 0) {
		correctYaw = 360 + sensorYaw;
		direction = -1.0;
	}
	else {
		correctYaw = sensorYaw;
		direction = 1.0;
	}

	Robot::driveTrain->DirectDrive(output*direction, output*direction);
}

// Make this return true when this Command no longer needs to run execute()
bool Rotate::IsFinished() {
    if (fabs( targetAngle - GetCorrectAngle(Robot::imu->GetYaw()) ) < 4) {	//if the difference between the sought angle and
    																	//the current angle is small enough,
    																	//the command will end
    	std::cout << "done rotating" << std::endl;
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

float Rotate::GetCorrectAngle(float angle) {
	if (angle < 0) {
		return 360 + angle;
	}
	else {
		return angle;
	}
}
