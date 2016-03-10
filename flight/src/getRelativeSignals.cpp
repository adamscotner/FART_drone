/*
	THIS FILE IS BROKEN AF.
	DO NOT USE
*/

#include "getRelativeSignals.h"


/// move these into a class
#define X 0
#define Y 1
#define Z 2
#define X_MAX 1
#define Y_MAX 1
#define Z_MAX 1
#define MAX_POWER_THRESH_X 0.75
#define MAX_POWER_THRESH_Y 0.75
#define MAX_POWER_THRESH_Z 0.75

using namespace std;

/*
	Get the new relative values (%) of Yaw, Pitch, Roll, and Throttle
*/
float[] getRelativeSignals(float[] object, float skew, float[] target)
{

	// float MAX_DIST[] = { 1, 1, 1 };
	// float MIN_X = -1, MIN_Y = -1, MIN_Z = -1;
	// float MAX_POWER_DIST[] = { 0.75, 0.75, 0.75 };


	// target[0] | [-1, 1] => roll => newSignals[2] | [0, 1]
	// target[1] | [-1, 1] => throttle => newSignals[3] | [0, 1]
	// target[2] | [-1, 1] => pitch => newSignals[1] | [1, 0]
	// skew | [-1, 1] => yaw => newSignals[0 | [0, 1]

	float sigArray[] = {
		positionToSignal(skew, false),      // yaw
		positionToSignal(target[2], true),  // pitch
		positionToSignal(target[0], false), // roll
		positionToSignal(target[1], false)  // throttle
	};

	// create vector from float array
	// vector<float> newSignals (sigArray, sigArray + sizeof(sigArray) / sizeof(float) );

	return sigArray;

}

/*
	Get the translated relative value, from [-1, 1] to [0, 1] or [1, 0], depending on
	the value of reverse
*/
float positionToSignal(float rel_pos, bool reverse)
{
	//TODO: check values and throw appropriate error

	// if the object is beyond the threshold to trigger maximum power,
	// force maximum power, else scale distance accordingly
	if (abs(rel_pos) > MAX_POWER_DIST) 
	{
		rel_pos = (rel_pos > 0) ? 1 | -1; 
	}
	else
	{
		rel_pos = rel_pos * (MAX_X / MAX_POWER_DIST);
	}

	rel_pos = reverse ? (-1 * rel_pos) : rel_pos;

	return (rel_pos / 2) + 0.5;
}