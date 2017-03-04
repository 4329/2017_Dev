#include "Rotate.h"

Rotate::Rotate(float Angle): Command() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::driveTrain.get());

	angle = Angle + 4;	//so the robot aims for 4 above the angle and stops at the angle
	output = 0.2;
}

// Called just before this Command runs the first time
void Rotate::Initialize() {
	std::cout << "now rotating " << angle << std::endl;
	Robot::driveTrain->SetVoltageMode();
	Robot::imu->Reset(); //reset yaw angle to 0
}

// Called repeatedly when this Command is scheduled to run
void Rotate::Execute() {
	std::cout << "Yaw: " << Robot::imu->GetYaw() << std::endl;

	//check if the robot went past the sought angle
	if (fabs(angle) < fabs(Robot::imu->GetYaw())) {
		output = -fabs(output);	//output is always negative(opposite direction that it started with)
	}
	else {
		output = fabs(output);	//output is always positive(same direction that it started with)
	}

	if (angle > 0) { //move left(when output is positive)
		Robot::driveTrain->DirectDrive(output, -output);
	}
	else {	//moving right(when output is positive)
		Robot::driveTrain->DirectDrive(-output, output);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool Rotate::IsFinished() {
    if (fabs( fabs(angle) - fabs(Robot::imu->GetYaw()) ) < 4) {	//if the difference between the sought angle and
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
