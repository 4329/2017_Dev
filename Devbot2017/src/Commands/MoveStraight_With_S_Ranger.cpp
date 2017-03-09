#include "MoveStraight_With_S_Ranger.h"
#include "../I2C_Sensor_Mgr.h"

MoveStraight_With_S_Ranger::MoveStraight_With_S_Ranger(bool forward, double cm_target_distance): Command() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::driveTrain.get());

    if (forward) {
    	output = 0.225;
    }
    else {
    	output = -0.225;
    }

    distance = 0.0;
    target_distance = cm_target_distance;
}

// Called just before this Command runs the first time
void MoveStraight_With_S_Ranger::Initialize() {
	std::cout << "now moving straight" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void MoveStraight_With_S_Ranger::Execute() {
	Robot::driveTrain->DirectDrive(output, output);
}

// Make this return true when this Command no longer needs to run execute()
bool MoveStraight_With_S_Ranger::IsFinished() {
	I2C_Sensor_Mgr::Instance()->Update_ShooterRangeFinder();
	distance = I2C_Sensor_Mgr::Instance()->Get_ShooterRange_cm();

	if (output > 0) {
		if (distance < target_distance) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (distance > target_distance) {
			return true;
		}
		else {
			return false;
		}
	}
}

// Called once after isFinished returns true
void MoveStraight_With_S_Ranger::End() {
	Robot::driveTrain->StopMotors();
	std::cout << "done moving straight" << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveStraight_With_S_Ranger::Interrupted() {

}
