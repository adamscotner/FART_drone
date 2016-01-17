#include "geRelativeSignals.h"

using namespace std;

/*
	Get the new relative values (%) of Yaw, Pitch, Roll, and Throttle
*/
vector<float> getRelativeSignals(vector<float> target, float skew, vector<float> idealLoc, vector<float> prevSignals)
{
	// if the target is already in the ideal location, maintain all signals
	if (target == idealLoc)
		return prevSignals;

	// otherwise, calculate the new values

	// target[0] | [-1, 1] => roll => newSignals[2] | [0, 1]
	// target[1] | [-1, 1] => throttle => newSignals[3] | [0, 1]
	// target[2] | [-1, 1] => pitch => newSignals[1] | [1, 0]
	// skew | [-1, 1] => yaw => newSignals[0 | [0, 1]

	float sigArray[] = {
		checkAndTranslate(skew, false),
		checkAndTranslate(target[2], true),
		checkAndTranslate(target[0], false),
		checkAndTranslate(target[1], false)
	};

	// create vector from float array
	vector<float> newSignals (sigArray, sigArray + sizeof(sigArray) / sizeof(float) );

	return newSignals;

}

/*
	Get the translated relative value, from [-1, 1] to [0, 1] or [1, 0], depending on
	the value of reverse
*/
float translateVal(float orig, bool reverse)
{
	//TODO: check values and throw appropriate error

	orig = reverse ? (-1 * orig) : orig;

	return (orig + 1) / 2;
}