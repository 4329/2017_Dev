/*
 * MotionController.h
 *
 *  Created on: Feb 24, 2017
 *      Author: mdbal
 */

#ifndef SRC_MOTIONCONTROLLER_H_
#define SRC_MOTIONCONTROLLER_H_

#include <vector>
#include <map>
#include <string>
#include <iomanip>
#include "WPILib.h"
#include "CANTalon.h"

typedef struct
{
	int index;
	std::vector<CANTalon::TrajectoryPoint> Points;
} mprofile;

class MotionController {
public:
	MotionController(std::string device, std::shared_ptr<CANTalon> talon);
	~MotionController();

	void AddProfile(int index, double profilepoints[][3], int Size, int gainslot);

	bool SetActiveProfile(int index);

	void Start();

	void Control();

	void Stop();

	void Reset();

	CANTalon::SetValueMotionProfile GetSetValue();

	bool ProfileInProgress();
	bool ProfileComplete();

	void EnableDebug(bool enable = true);

protected:
	friend Notifier;

	void PeriodicTask();

private:
	void SendProfile();

	void OnNoProgress();
	void OnUnderrun();
	const char * StrOutputEnable(unsigned int value);
	void OutputStatus(CANTalon::MotionProfileStatus & status);

	std::string _myDevice;
	bool _enableDebug;
	std::shared_ptr<CANTalon> _Talon;
	bool profileLoaded;
	double period;

	std::map<int,mprofile> _Profiles;
	int _currentProfile;
    bool _profileInProgress;
    bool _profileComplete;


	/**
	 * The status of the motion profile executer and buffer inside the Talon.
	 * Instead of creating a new one every time we call getMotionProfileStatus,
	 * keep one copy.
	 */
	CANTalon::MotionProfileStatus _Status;

	/**
	 * State machine to make sure we let enough of the motion profile stream to
	 * talon before we fire it.
	 */
	int _State;


	/**
	 * Any time you have a state machine that waits for external events, its a
	 * good idea to add a timeout. Set to -1 to disable. Set to nonzero to count
	 * down to '0' which will print an error message. Counting loops is not a
	 * very accurate method of tracking timeout, but this is just conservative
	 * timeout. Getting time-stamps would certainly work too, this is just
	 * simple (no need to worry about timer overflows).
	 */
	int _loopTimeout;
	/**
	 * If start() gets called, this flag is set and in the control() we will
	 * service it.
	 */
	bool _Start;

	/**
	 * Since the CANTalon.set() routine is mode specific, deduce what we want
	 * the set value to be and let the calling module apply it whenever we
	 * decide to switch to MP mode.
	 */
	CANTalon::SetValueMotionProfile _setValue;

	/**
	 * How many trajectory points do we wait for before firing the motion
	 * profile.
	 */
	static const int kMinPointsInTalon = 5;

	/**
	 * Just a state timeout to make sure we don't get stuck anywhere. Each loop
	 * is about 20ms.
	 */
	static const int kNumLoopsTimeout = 10;

	/**
	 * Lets create a periodic task to funnel our trajectory points into our talon.
	 * It doesn't need to be very accurate, just needs to keep pace with the motion
	 * profiler executer.
	 */
	Notifier _notifer;

};

#endif /* SRC_MOTIONCONTROLLER_H_ */
