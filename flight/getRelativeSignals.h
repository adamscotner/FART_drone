#include <iostream>
#include <vector>
#include <algorithm>

/*
	Get the new relative values (%) of Yaw, Pitch, Roll, and Throttle
	parameters: 
		vector<float> target
			A set of three-dimensional cartesian coordinates indicating the location
			of an object, within [-1, 1], relative to the drone located at [0, 0, -1].
		float skew
			A numeric representation of x-axis skew,, within [-1, 1], where -1 represents
			maximum recognzable skew left, and vice versa.
		vector<float> idealLoc
			a set of three-dimensional cartesian coordinates indicationg the ideal
			placement of the target object, relative to the drone at [0, 0, -1].
		vecotr<float> prevSignals
			A set of 4 values of range [0, 1] indicating the previous values of 
			relative power to be applied to yaw, pitch, roll, and throttle.
	returns: vector<float>
		A set of 4 values of range [0, 1] indicating the relative power to be applied
		to yaw, pitch, roll, and throttle.
*/

vector<float> getRelativeSignals(vector<float> target, float skew, vector<float> idealLoc, vector<float> prevSignals);

/*
	Get the translated relative value, from [-1, 1] to [0, 1] or [1, 0], depending on
	the value of 'reverse'.
	parameters:
		float orig
			value between [-1, 1] representing relative position on any axis
		bool reverse
			translate 'orig' to [0, 1] or [1, 0]
	returns: float
		translated value
*/
float translateVal(float orig, bool reverse);