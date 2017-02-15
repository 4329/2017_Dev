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
	Block * block_ptr;	//points to the correct block (the 15 in. by 4 in. one)
	double new_ratio;	//the w/h ratio of the newest block
	double old_ratio;	//the w/h ratio of the previous block
	double new_ratio_diff;	//the difference of the new ratio to high block ratio
	double old_ratio_diff;	//the difference of the old ratio to high block ratio


	pixy->signatures.clear();	//get rid of old blocks
	pixy->GetBlocks();	//add new blocks

	int num_of_blocks = pixy->signatures.size();

	block_ptr = pixy->signatures[0];	//make the first block the default
	new_ratio = pixy->signatures[0].width / pixy->signatures[0].height;

	for(int i = 1; i < (num_of_blocks - 1); i++) {
		//gets ratios
		old_ratio = new_ratio;
		new_ratio = pixy->signatures[i].width / pixy->signatures[i].height;
	}
}
