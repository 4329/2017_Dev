#include "GearPixy.h"
#include "../RobotMap.h"
#include "../I2C_Sensor_Mgr.h"


GearPixy::GearPixy() : Subsystem("GearPixy") {

}

void GearPixy::InitDefaultCommand() {
    // Set the default command for a subsystem here.
    // SetDefaultCommand(new MySpecialCommand());

}


// Put methods for controlling this subsystem
// here. Call these from Commands.

Block * GearPixy::Get_Target() {
//Set Up
	Block * block_ptr;	//points to the correct block (the 15 in. by 4 in. one)
	double new_ratio;	//the w/h ratio of the newest block
	double old_ratio;	//the w/h ratio of the previous block
	double new_ratio_diff;	//the difference of the new ratio to high block ratio
	double old_ratio_diff;	//the difference of the old ratio to high block ratio

	I2C_Sensor_Mgr::Instance()->Update_GearPixy();
	std::vector<Block> sigs = I2C_Sensor_Mgr::Instance()->Get_GearSignatures();

	int num_of_blocks = sigs.size();
	std::cout << "GearPixy: number of targets: " << num_of_blocks << std::endl;

	//print block values
	for(int i = 0; i < num_of_blocks; i++) {	//print values of all blocks
			std::cout << "block " << i + 1 << ": x: " << sigs[i].x << ", ";
			std::cout << "y: " << sigs[i].y << ", ";
			std::cout << "width: " << sigs[i].width << ", ";
			std::cout << "height: " << sigs[i].height << ", ";
			std::cout << "w/h: " << sigs[i].width / sigs[i].height << std::endl;
	}

//more than 2 blocks
	if (num_of_blocks > 2) {	//checks for the top target by ratios

		block_ptr = &sigs[0];	//make the first block the default
		new_ratio = sigs[0].width / sigs[0].height;

		for(int i = 1; i < num_of_blocks; i++) {
			//gets ratios
			old_ratio = new_ratio;
			new_ratio = sigs[i].width / sigs[i].height;

			//gets ratio differences
			old_ratio_diff = abs(high_block_ratio - old_ratio);
			new_ratio_diff = abs(high_block_ratio - new_ratio);

			//assign the block that has the least difference
			if (new_ratio_diff < old_ratio_diff) {
				block_ptr = &sigs[i];	//new block is the pointed to
			}
			else {	//if (new_ratio_diff > old_ratio_diff)
				block_ptr = &sigs[i-1];	//old block is pointed to
			}
		}

	}
//only 2 blocks (extremely good chance that these 2 blocks are the 2 reflective tape strips on the boiler)
	else if (num_of_blocks == 2) {	//checks for the top target by y values

		if ( sigs[0].y > sigs[1].y ) {
			block_ptr = &sigs[0];	//the first block is pointed to; it is the top target as the y value is greater
		}
		else {	//if (pixy->signatures[1].y > pixy->signatures[0].y)
			block_ptr = &sigs[1];	//the second block is pointed to; it is the top target as the y value is greater
		}

	}

//only 1 block
	else if (num_of_blocks == 1) {	//return the 1 target on the pixy cam
		block_ptr = &sigs[0];
	}

//other case
	else {
		block_ptr = 0;	//pointer will be null as there are probably no blocks or something went wrong
						//shooter command should be canceled in this case
	}

	return block_ptr;
}

float GearPixy::Distance_From_Target() {	//doesn't need to account for the target being off-centered as this function will be called
											//after the robot has faced towards the target
	Block * block_ptr = Get_Target();

	//look at the end of this for details: http://wpilib.screenstepslive.com/s/4485/m/24194/l/288985-identifying-and-processing-the-targets
	//gets distance from pixy directly to the tape
	float distance = (15.0 * 319.0) / (2 * block_ptr->width * tan( ((H_FOV / 2.0) * pi)) / 180.0);
	std::cout << "GearPixy: direct distance: " << distance << std::endl;

	// (y_pixels) / (target_y_value) = V_HOV / angle
	// target_y_value * V_HOV = y_pixels * angle
	float angle = (block_ptr->y * V_FOV) / 199.0;
	angle = angle + 0;	//0 is a placeholder for the angle the pixy cam is tilted (will be in config)

	// cos( (angle * pi) /180.0 ) = (horizontal distance) / (direct distance)
	distance = cos(  (angle * pi) / 180.0 ) * distance;
	std::cout << "GearPixy: horizontal distance: " << distance << std::endl;

	return distance;
}

void GearPixy::printBlockData() {
	I2C_Sensor_Mgr::Instance()->Update_GearPixy();
	std::vector<Block> sigs = I2C_Sensor_Mgr::Instance()->Get_GearSignatures();

	int num_of_blocks = sigs.size();
	std::cout << "GearPixy: number of targets: " << num_of_blocks << std::endl;

	//print block values
	for(int i = 0; i < num_of_blocks; i++) {	//print values of all blocks
			std::cout << "block " << i + 1 << ": x: " << sigs[i].x << ", ";
			std::cout << "y: " << sigs[i].y << ", ";
			std::cout << "width: " << sigs[i].width << ", ";
			std::cout << "height: " << sigs[i].height << ", ";
			std::cout << "w/h: " << sigs[i].width / sigs[i].height << std::endl;
	}
}

bool GearPixy::OnTarget() {
	if ( abs(Angle_From_Target()) < 5) {	//5 is a place holder (final number will be in config file)
		return true;
	}
	else {
		return false;
	}
}

float GearPixy::Angle_From_Target() {	//if angle is positive, robot turns right; if angle is negative, robot turns left
	Block * block_ptr = Get_Target();

	// ( Pixy_pixels_on_1_side / block_ptr->x_deviation ) = ( (H_FOV / 2) / angle_from_target)
	// block_ptr->x_deviation * (H_FOV / 2) = Pixy_pixels_on_1_side * angle_from_target
	return  (block_ptr->x_deviation * (H_FOV / 2) ) / 160.0;
}
