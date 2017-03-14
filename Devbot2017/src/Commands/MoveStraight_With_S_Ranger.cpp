#include "../I2C_Sensor_Mgr.h"
#include "MoveStraight_With_S_Ranger.h"

MoveStraight_With_S_Ranger::MoveStraight_With_S_Ranger(bool forward, double cm_target_distance): Command() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::driveTrain.get());

    //forward is the intake side

    _forward = forward;
    if (_forward) {
    	output = -0.3;	//robot will move in the direction of the intake
    }
    else {
    	output = 0.3;	//robot will move in the direction of the gear holder
    }

    distance = 0.0;
    target_distance = cm_target_distance;

    count = 0;

    error = 0.0;
}

// Called just before this Command runs the first time
void MoveStraight_With_S_Ranger::Initialize() {
	Robot::imu->ZeroYaw();	//resets the yaw before the command
	std::cout << "4329 Log: " << GetTime() << ", now moving straight" << std::endl;
}

// Called repeatedly when this Command is scheduled to run
void MoveStraight_With_S_Ranger::Execute() {
	Robot::driveTrain->HeadingDrive(output);	//move forward or backwards
}

// Make this return true when this Command no longer needs to run execute()
bool MoveStraight_With_S_Ranger::IsFinished() {
	//get distance from ultrasonic sensor
	I2C_Sensor_Mgr::Instance()->Update_ShooterRangeFinder();
	distance = I2C_Sensor_Mgr::Instance()->Get_ShooterRange_cm();

	std::cout << "MS distance: " << distance << std::endl;

	if (distance > 800) {
		count++;
		return false;
	}
	else {
		count = 0;
	}

	if (count > 10) { //stop if the numbers have been off for too long
		return true;
	}

	if (_forward) {	//distance should be decreasing, so stop when it's less than a certain distance
		if (distance <= (target_distance - error)) {
			Robot::driveTrain->StopMotors(); //stop early
			return true;
		}
		else {
			return false;
		}
	}
	else {	//distance should be increasing, so stop when it's past than a certain distance
		if (distance >= (target_distance + error)) {
			Robot::driveTrain->StopMotors();
			return true;
		}
		else {
			return false;
		}
	}
}

// Called once after isFinished returns true
void MoveStraight_With_S_Ranger::End() {
	Robot::imu->ZeroYaw();	//resets the yaw before the next usage
	std::cout << "4329 Log: " << GetTime() << ", done moving straight" << std::endl;
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void MoveStraight_With_S_Ranger::Interrupted() {

}
