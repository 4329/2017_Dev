#include "AlignShoot.h"

AlignShoot::AlignShoot(): Command() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::driveTrain.get());
    output = 0.225;
    distance = 20;	//just for set up

}

// Called just before this Command runs the first time
void AlignShoot::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AlignShoot::Execute() {
	Block* block = Robot::gearPixy->Get_Target();
	distance = block->x_deviation;

	//neg right, pos left
	if (distance < 0) {
		Robot::driveTrain->DirectDrive(output, -output);
	}
	else {
		Robot::driveTrain->DirectDrive(-output, output);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AlignShoot::IsFinished() {
	//can't check if distance is less than an small number or else the robot will shuffle back and forth
	if (fabs(distance) + 9.5 < 10) {	//adds 9.5 so robot doesn't stop 10 units short
		return true;
	}
	else {
		return false;
	}
}

// Called once after isFinished returns true
void AlignShoot::End() {
	Robot::driveTrain->StopMotors();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AlignShoot::Interrupted() {

}
