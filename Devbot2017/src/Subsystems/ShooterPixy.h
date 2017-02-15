#ifndef SHOOTERPIXY_H
#define SHOOTERPIXY_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../Pixy.h"

#define low_block_ratio		15/4	//   width / height
#define high_block_ratio	15/2	//   width / height
#define H_FOV 75	//(horizontal field of view) whole view: 75 degrees, half view 75/2 (36.5) degrees
#define V_FOV 47	//(vertical field of view) whole view: 47 degrees, half view 47/2 (23.5) degrees

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

	uint16_t _10bit_to_16bit(int num);
	int _16bit_to_10bit(uint16_t num);
};

#endif
