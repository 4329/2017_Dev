#ifndef SHOOTERPIXY_H
#define SHOOTERPIXY_H
#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../Pixy.h"

#define low_block_ratio		15/4	//   width / height
#define high_block_ratio	15/2	//   width / height

/**
 *
 *
 * @author ExampleAuthor
 */
class ShooterPixy: public Subsystem {
private:
	// It's desirable that everything possible is private except
	// for methods that implement subsystem capabilities
	Block * block_ptr;
	std::shared_ptr<Pixy> pixy;

public:
	ShooterPixy();
	void InitDefaultCommand();

	uint16_t * Get_Target_Values();	//return an array with the values of the target
	float Distance_From_Target(); //uses trig to check how far the shooter is from the target (boiler)
	bool OnTarget();	//check if shooter is facing boiler

	uint16_t _10bit_to_16bit(int num);
	int _16bit_to_10bit(uint16_t num);
};

#endif
