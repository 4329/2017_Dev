#include "Rotate.h"

Rotate::Rotate(float Angle): Command() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::driveTrain.get());

	angle = Angle;
	output = 1;	//all output ranges between 0.1 and 2(if angle isn't > 180)
}

// Called just before this Command runs the first time
void Rotate::Initialize() {
	Robot::imu->Reset(); //reset yaw angle to 0
}

// Called repeatedly when this Command is scheduled to run
void Rotate::Execute() {
	if (angle > 0) { //move right(when output is positive)
		Robot::driveTrain->TankDrive(output, -output);
	}
	else {	//moving left(when output is positive)
		Robot::driveTrain->TankDrive(-output, output);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool Rotate::IsFinished() {
	//output is smaller as robot gets closer to the sought angle
	float diff = abs( angle - Robot::imu->GetYaw() );
	output = diff / 90;	//output should be 1 when it is 90 degrees away from the sought angle
	if (output < 0.1) {
		output = 0.1;	//output is no less than .1
	}

	if (angle < Robot::imu->GetYaw()) {	//check if the robot went past the sought angle
		output = -abs(output);	//output is always negative(opposite direction that it started with)
	}
	else {
		output = abs(output);	//output is always positive(same direction that it started with)
	}


    if (abs( angle - Robot::imu->GetYaw() ) < 4) {	//if the difference between the sought angle and
    																	//the current angle is small enough,
    																	//the command will end
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
