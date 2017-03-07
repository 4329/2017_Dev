/*
 * MotionController.cpp
 *
 *  Created on: Feb 24, 2017
 *      Author: mdbal
 */

#include "MotionController.h"

MotionController::MotionController(std::string device, std::shared_ptr<CANTalon> talon) : _notifer(&MotionController::PeriodicTask, this)
{
	_myDevice = device;
	_Talon = talon;

	if (_Talon) {
		std::cout << "motion control talon exists" << std::endl;
	}

	_State = 0;
	_Profiles.clear();
	_currentProfile = -1;
	profileLoaded = false;
	period = 0.0;
	_setValue = CANTalon::SetValueMotionProfileDisable;
	_Start = false;
	_loopTimeout = -1;
	_profileInProgress = false;
	_profileComplete = false;
	_enableDebug = false;
}

MotionController::~MotionController() {
	_Profiles.clear();
}

void MotionController::PeriodicTask()
{
	/* keep Talons happy by moving the points from top-buffer to bottom-buffer */
	if (_Talon) _Talon->ProcessMotionProfileBuffer();
}

void MotionController::AddProfile(int index, double profilepoints[][3], int Size, int gainslot)
{
	mprofile pfile;
	pfile.index = index;

	for (int i = 0; i < Size; i++)
	{
		CANTalon::TrajectoryPoint point;

		// copy the position, velocity, and time from current row
		point.position = profilepoints[i][0];
		point.velocity = profilepoints[i][1];
		point.timeDurMs = (int) profilepoints[i][2];

		// which set of gains would you like to use?
		point.profileSlotSelect = gainslot;

		point.velocityOnly = false;

        // set true to not do any position servo, just velocity feedforward
		point.zeroPos = false;

		if (i == 0)
			point.zeroPos = true; /* set this to true on the first point */

		point.isLastPoint = false;

		if( (i + 1) == Size )
			point.isLastPoint = true; // set this to true on the last point

		pfile.Points.push_back(point);
	}
	_Profiles[index] = pfile;
}

bool MotionController::SetActiveProfile(int index)
{
	std::map<int,mprofile>::iterator itt = _Profiles.find(index);

	if (itt != _Profiles.end())
	{
		_currentProfile = index;
		return true;
	}
	return false;
}

// Loads Talon driver buffer for background transfer to the Talon over CAN.
void MotionController::SendProfile()
{
	period = 0.0;
	profileLoaded = false;

	if (_currentProfile == -1) return;

	/* did we get an underrun condition since last time we checked ? */
	if(_Status.hasUnderrun){
		/* better log it so we know about it */
		OnUnderrun();
		/*
		 * clear the error. This is what seperates "has underrun" from
		 * "is underrun", because the former is cleared by the application.
		 * That way, we never miss logging it.
		 */
		_Talon->ClearMotionProfileHasUnderrun();
	}

	/*
	 * just in case we are interrupting another MP and there is still buffer
	 * points in memory, clear it.
	 */
	_Talon->ClearMotionProfileTrajectories();

	mprofile theProfile = _Profiles[_currentProfile];

	if (!theProfile.Points.empty())
	{
		std::vector<CANTalon::TrajectoryPoint>::iterator itt = theProfile.Points.begin();
		int mcfp = (int) floor((double) itt->timeDurMs / 2.0);
		period = (double) mcfp / 1000.0;

		if (_Talon)
		{
			_Talon->ChangeMotionControlFramePeriod(mcfp);

			while (itt != theProfile.Points.end())
			{
				_Talon->PushMotionProfileTrajectory(*itt);
				itt++;
			}
			profileLoaded = true;
		}
	}
}

void MotionController::Start()
{
	if (profileLoaded)
	{
		_Start = true;
		_Talon->SetControlMode(CANSpeedController::kMotionProfile);

		/* start our tasking */
		_notifer.StartPeriodic(period);
	}
}

void MotionController::Control()
{
	/* Get the motion profile status every loop */
	_Talon->GetMotionProfileStatus(_Status);

	/*
	 * track time, this is rudimentary but that's okay, we just want to make
	 * sure things never get stuck.
	 */
	if (_loopTimeout < 0)
	{
		/* do nothing, timeout is disabled */
	} else
	{
		/* our timeout is nonzero */
		if (_loopTimeout == 0)
		{
			/*
			 * something is wrong. Talon is not present, unplugged, breaker
			 * tripped
			 */

			OnNoProgress();
		} else
		{
			--_loopTimeout;
		}
	}

	/* first check if we are in MP mode */
	if(_Talon->GetControlMode() != CANSpeedController::kMotionProfile)
	{
		/*
		 * we are not in MP mode. We are probably driving the robot around
		 * using gamepads or some other mode.
		 */
		_State = 0;
	} else
	{
		/*
		 * we are in MP control mode. That means: starting Mps, checking Mp
		 * progress, and possibly interrupting MPs if thats what you want to
		 * do.
		 */
		switch (_State)
		{
			case 0: /* wait for application to tell us to start an MP */
				if (_Start)
				{
					_Start = false;

					_setValue = CANTalon::SetValueMotionProfileDisable;
					_Talon->Set(_setValue);
					SendProfile();
					/*
					 * MP is being sent to CAN bus, wait a small amount of time
					 */
					_State = 1;
					_loopTimeout = kNumLoopsTimeout;
				}
				break;
			case 1: /*
					 * wait for MP to stream to Talon, really just the first few
					 * points
					 */
				/* do we have a minimum numberof points in Talon */
				if (_Status.btmBufferCnt > kMinPointsInTalon)
				{
					/* start (once) the motion profile */
					_setValue = CANTalon::SetValueMotionProfileEnable;
					_Talon->Set(_setValue);
					/* MP will start once the control frame gets scheduled */
					_State = 2;
					_profileInProgress = true;
					_loopTimeout = kNumLoopsTimeout;
				}
				break;
			case 2: /* check the status of the MP */
				/*
				 * if talon is reporting things are good, keep adding to our
				 * timeout. Really this is so that you can unplug your talon in
				 * the middle of an MP and react to it.
				 */
				if (_Status.isUnderrun == false)
				{
					_loopTimeout = kNumLoopsTimeout;
					_profileInProgress = true;
				}
				/*
				 * If we are executing an MP and the MP finished, start loading
				 * another. We will go into hold state so robot servo's
				 * position.
				 */
				if (_Status.activePointValid && _Status.activePoint.isLastPoint)
				{
					/*
					 * because we set the last point's isLast to true, we will
					 * get here when the MP is done
					 */
					_setValue = CANTalon::SetValueMotionProfileHold;
					_Talon->Set(_setValue);
					_State = 0;
					_loopTimeout = -1;
					_profileComplete = true;
				}
				break;
		}
	}
	OutputStatus(_Status);
}



void MotionController::Stop()
{
	Reset();
}

void MotionController::Reset()
{
	/*
	 * Let's clear the buffer just in case user decided to disable in the
	 * middle of an MP, and now we have the second half of a profile just
	 * sitting in memory.
	 */
	_Talon->ClearMotionProfileTrajectories();
	/* When we do re-enter motionProfile control mode, stay disabled. */
	_setValue = CANTalon::SetValueMotionProfileDisable;
	_Talon->Set(_setValue);

	/* When we do start running our state machine start at the beginning. */
	_State = 0;
	_loopTimeout = -1;
	_Start = false;
	_profileInProgress = false;
	_profileComplete = true;

}

bool MotionController::ProfileInProgress()
{
	return _profileInProgress;
}

bool MotionController::ProfileComplete()
{
	return _profileComplete;
}

CANTalon::SetValueMotionProfile MotionController::GetSetValue()
{
	return _setValue;
}

void MotionController::EnableDebug(bool enable)
{
	_enableDebug = enable;
}

void MotionController::OnNoProgress()
{
	if(!_enableDebug) return;
	double now = GetTime();
	std::cout << "4329_DEBUG:" << now << "MotionController:" << _myDevice << ":NOPROGRESS" << std::endl;
}

void MotionController::OnUnderrun()
{
	if(!_enableDebug) return;
	double now = GetTime();
	std::cout << "4329_DEBUG:" << now << "MotionController:" << _myDevice << ":UNDERRUN\n";
}

const char * MotionController::StrOutputEnable(unsigned int value)
{
	static const char table[][6] = {" Dis "," En  ","Hold ","Inval"};
	if(value > 3)
		value = 3;
	return table[value];
}
/**
 * Prints and/or logging to watch the MP signals
 */
void MotionController::OutputStatus(CANTalon::MotionProfileStatus & status)
{
	static double timeout = 0;

	if(!_enableDebug) return;

	double now = GetTime();

	if((now-timeout) > 0.2)
	{
		timeout = now;
		/* fire a loop every 200ms */

		std::cout << "4329_DEBUG:" << now << "MotionController:" << _myDevice
				<< ":outputEnable:" << StrOutputEnable(status.outputEnable)
				<< ":topBufferRem:" << status.topBufferRem
				<< ":topBufferCnt:" << status.topBufferCnt
				<< ":btmBufferCnt:" << status.btmBufferCnt
				<< ":IsValid:" << (status.activePointValid ? "1" : "")
				<< ":HasUnderrun:" << (status.hasUnderrun ? "1" : "")
				<< ":IsUnderrun:" << (status.isUnderrun ? "1" : "")
				<< ":IsLast:" << (status.activePoint.isLastPoint ? "1" : "")
				<< ":VelOnly:" << (status.activePoint.velocityOnly ? "1" : "")
				<< ":targPos:" << status.activePoint.position
				<< ":targVel:" << status.activePoint.velocity
				<< ":profSlotSel:" << status.activePoint.profileSlotSelect
				<< ":timeDurMs:" << status.activePoint.timeDurMs << std::endl;
	}
}

