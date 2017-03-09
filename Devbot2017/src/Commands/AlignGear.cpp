#include "AlignGear.h"

AlignGear::AlignGear(): Command() {
        // Use requires() here to declare subsystem dependencies
    Requires(Robot::driveTrain.get());

    output = 0.225;
    distance = 10;	//set for set up
}

// Called just before this Command runs the first time
void AlignGear::Initialize() {

}

// Called repeatedly when this Command is scheduled to run
void AlignGear::Execute() {
	std::vector<Block> sigs = Robot::gearPixy->Return_All_Targets();
	distance = Robot::gearPixy->X_Offset_From_Target(sigs);

	//pos right, neg left
	if (distance > 0) {
		Robot::driveTrain->DirectDrive(output, -output);
	}
	else {
		Robot::driveTrain->DirectDrive(-output, output);
	}
}

// Make this return true when this Command no longer needs to run execute()
bool AlignGear::IsFinished() {
	//can't check if distance is less than an small number or else the robot will shuffle back and forth
	if (fabs(distance) + 2.5 < 3) {	//adds 2.5 so robot doesn't stop 3 units short
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
