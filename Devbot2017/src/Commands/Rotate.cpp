#include "Rotate.h"

Rotate::Rotate(float Angle): Command() {
        // Use requires() here to declare subsystem dependencies
    // eg. requires(Robot::chassis.get());
	angle = Angle;
	overshot = false;
}

// Called just before this Command runs the first time
void Rotate::Initialize() {
	Robot::driveTrain->Get_imu()->ZeroYaw(); //reset angle
}

// Called repeatedly when this Command is scheduled to run
void Rotate::Execute() {
	float output = 1;
	if (overshot) {
		output *= -0.5;	//move slower and in the opposite direction
	}

	if (angle > 0) {	//move right
		Robot::driveTrain->TankDrive(output, -output);
	}
	else {	//moving left
		Robot::driveTrain->TankDrive(-output, output);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool Rotate::IsFinished() {
	if (angle < Robot::driveTrain->Get_imu()->GetYaw()) {	//check if the robot went past the sought angle
		overshot = true;
	}
	else {
		overshot = false;
	}

    if (abs( angle - Robot::driveTrain->Get_imu()->GetYaw() ) < 4) {	//if the difference between the sought angle and
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
