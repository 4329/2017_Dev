#include "ShooterPixy.h"
#include "../RobotMap.h"
#include "../Pixy.h"


ShooterPixy::ShooterPixy() : Subsystem("ShooterPixy") {
	pixy = RobotMap::pixy;
	block_ptr = 0;
}

void ShooterPixy::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());

}


// Put methods for controlling this subsystem
// here. Call these from Commands.

uint16_t * ShooterPixy::Get_Target_Values() {
	//to do: check if there more than 2 blocks
	//needs to be discussed
	/*
	pixy->signatures.clear();
	pixy->GetBlocks();
	int size = pixy->signatures.size();

	float ratio;	//the new width/height ratio of a block
	float last_ratio;	//the last checked width/height ratio of a block
	int high_block;	//the vector position of the high reflection tape strip
	int low_block;	//the vector position of the low reflection tape strip

	//gets the vector position of the high reflection tape strip
	for (int i = 0; i >= size; i++) {
			ratio = pixy->signatures[i].width / pixy->signatures[i].width;
	}
	*/
}
