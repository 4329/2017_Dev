#ifndef GEARPIXY_H
#define GEARPIXY_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../Pixy.h"
#include <cmath>

//ratios may be different depending on where the robot is on the field
#define low_block_ratio		15/2	//   width / height
#define high_block_ratio	15/4	//   width / height
#define H_FOV 60.0f	//(horizontal field of view) whole view: 60 degrees, half view 60/2 (30) degrees
#define V_FOV 35.0f	//(vertical field of view) whole view: 35 degrees, half view 35/2 (17.5) degrees
#define pi 3.14159265358979323846f	//the f means that it is a float

/**
 *
 *
 * @author ExampleAuthor
 */
class GearPixy: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities

public:
	GearPixy();
	void InitDefaultCommand();

	Block * Get_Target();	//return the correct target
	float Distance_From_Target(); //gets horizontal distance from the pixy to the target (boiler) in inches
	float Angle_From_Target();
	bool OnTarget();	//check if shooter is facing boiler

	void printBlockData();

	//float _16bit_to_10bit(uint16_t _16bit_num);
};

#endif
