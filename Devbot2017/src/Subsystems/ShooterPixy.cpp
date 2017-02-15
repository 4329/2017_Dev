#include "ShooterPixy.h"
#include "../RobotMap.h"
#include "../Pixy.h"


ShooterPixy::ShooterPixy() : Subsystem("ShooterPixy") {
	pixy = RobotMap::pixy;
}

void ShooterPixy::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());

}


// Put methods for controlling this subsystem
// here. Call these from Commands.

Block * ShooterPixy::Get_Target() {
	//do error handling of 0 blocks
	//Possibly check which is the correct block by y value

	Block * block_ptr;	//points to the correct block (the 15 in. by 4 in. one)
	double new_ratio;	//the w/h ratio of the newest block
	double old_ratio;	//the w/h ratio of the previous block
	double new_ratio_diff;	//the difference of the new ratio to high block ratio
	double old_ratio_diff;	//the difference of the old ratio to high block ratio


	pixy->signatures.clear();	//get rid of old blocks
	pixy->GetBlocks();	//add new blocks

	int num_of_blocks = pixy->signatures.size();
	std::cout << "ShooterPixy: number of targets: " << num_of_blocks << std::endl;

	block_ptr = &pixy->signatures[0];	//make the first block the default
	new_ratio = pixy->signatures[0].width / pixy->signatures[0].height;

	for(int i = 1; i < (num_of_blocks - 1); i++) {
		//gets ratios
		old_ratio = new_ratio;
		new_ratio = pixy->signatures[i].width / pixy->signatures[i].height;

		//gets ratio differences
		old_ratio_diff = abs(high_block_ratio - old_ratio);
		new_ratio_diff = abs(high_block_ratio - new_ratio);

		//assign the block that has the least difference
		if (new_ratio_diff < old_ratio_diff) {
			block_ptr = &pixy->signatures[i];	//new block is the pointed to
		}
		else {	//if (new_ratio_diff > old_ratio_diff)
			block_ptr = &pixy->signatures[i-1];	//old block is pointed to
		}
	}

	pixy->signatures.clear();
	return block_ptr;
}

float ShooterPixy::Distance_From_Target() {	//for now, this assumes that the pixy is facing horizontally
	Block * block_ptr = Get_Target();

	//look at the end of this for details: http://wpilib.screenstepslive.com/s/4485/m/24194/l/288985-identifying-and-processing-the-targets
	//gets distance from pixy directly to the tape
	float distance = (15.0 * 319.0) / (2 * block_ptr->width * tan( ((H_FOV / 2.0) * pi)) / 180.0);
	std::cout << "ShooterPixy: direct distance: " << distance << std::endl;

	// cos(V_FOV / 2) = (horizontal distance) / (direct distance)
	distance = cos( V_FOV / 2.0) * distance;
	std::cout << "ShooterPixy: horizontal distance: " << distance << std::endl;

	return distance;
}

void ShooterPixy::printBlockData() {
	pixy->signatures.clear();	//get rid of old blocks
	pixy->GetBlocks();	//add new blocks
	int num_of_blocks = pixy->signatures.size();

	for(int i = 0; i < num_of_blocks; i++) {	//print values of all blocks
			std::cout << "block1: x: " << pixy->signatures[i].x << ", ";
			std::cout << "y: " << pixy->signatures[i].y << ", ";
			std::cout << "width: " << pixy->signatures[i].width << ", ";
			std::cout << "height: " << pixy->signatures[i].height << ", ";
			std::cout << "w/h: " << pixy->signatures[i].width / pixy->signatures[i].height << std::endl;
	}

	pixy->signatures.clear();
}

bool ShooterPixy::OnTarget() {

}
