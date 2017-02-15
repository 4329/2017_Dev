#ifndef SHOOTERPIXY_H
#define SHOOTERPIXY_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../Pixy.h"
#include <cmath>

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
class ShooterPixy: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	std::shared_ptr<Pixy> pixy;

public:
	ShooterPixy();
	void InitDefaultCommand();

	Block * Get_Target();	//return the correct target
	float Distance_From_Target(); //uses trig to check how far the pixy is from the target (boiler)
								//gets distance that is from the pixy directly to the target
								//then does math and returns horizontal distance from pixy to tape
								//distance is in inches

	bool OnTarget();	//check if shooter is facing boiler

	void printBlockData();

	float _16bit_to_10bit(uint16_t _16bit_num);
};

#endif
