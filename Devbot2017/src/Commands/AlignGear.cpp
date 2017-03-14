#include "AlignGear.h"

AlignGear::AlignGear(): Command() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::driveTrain.get());

    output = 0.15;
    distance = 100;	//set for set up
    clockwise = true;
}

// Called just before this Command runs the first time
void AlignGear::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AlignGear::Execute() {
	std::vector<Block> sigs = Robot::gearPixy->Return_All_Targets();
	std::cout << "AG Made it here: "  << std::endl;

	if (sigs.size() > 0) {
		distance = Robot::gearPixy->X_Offset_From_Target(sigs);
		std::cout << "AG distance: " << distance << std::endl;

		//assumes gear holder is facing peg
		//distance > 0 means gear holder is to the left of the peg
		//distance < 0 means gear holder is to the right of peg
		if (distance > 0) {
			clockwise = true;
			Robot::driveTrain->DirectDrive(output, -output);
		}
		else {
			clockwise = false;
			Robot::driveTrain->DirectDrive(-output, output);
		}
	}
	else {	//if robot fails to see the targets
		if (clockwise) {
			Robot::driveTrain->DirectDrive(-output, output);//robot will go the opposite direction of it's direction when it did see blocks
		}
		else {
			Robot::driveTrain->DirectDrive(output, -output);
		}
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AlignGear::IsFinished() {
	//can't check if distance is less than an small number or else the robot will shuffle back and forth
	if (fabs(distance) < 10) {
		return true;
	}
	else {
		return false;
	}
}

// Called once after isFinished returns true
void AlignGear::End() {
	Robot::driveTrain->StopMotors();
}

// Called when another command which requires one or more of the same
// subsystems is scheduled to run
void AlignGear::Interrupted() {

}
