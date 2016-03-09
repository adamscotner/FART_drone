#ifndef SIGNALGENERATION_H
#define SIGNALGENERATION_H

#include "pca9685.h"
#include <wiringPi.h> 
#include <wiringPiI2C.h>
#include <stdio.h>
#include <stdlib.h>

#include "PWMChannel.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

/*
	SignalGeneration class
	-maintains copies of signals
	-translates positions into relative signals
	-translates relative signals into discrete PWM values
*/
class SignalGeneration
{
	private:
		// 3d cartesian coordinates indicating the tracked object's position
		std::vector<double> objectPosition;
		// 3d cartesian coordinates indicating the tracked object's previous position
		std::vector<double> prevObjectPosition;
		// 3d cartesian coordinates indicating the target position for the object
		std::vector<double> targetPosition;
		// array of control signal objects
		// [Yaw, Pitch, Roll, Throttle]
		std::vector<PWMChannel> signals;
		// maximum distance at which drone will apply mazimum power
		double maxPowerThresh;
		double maxPower;

	public:
		// constructor
		SignalGeneration ();
		// set previous and current object positions
		void newObjectPosition (double newPos[]);
		void assignSignals ();
		void assignSignals (double newPos[]);
		void calculateNewSignal (int, int);
		void print();

};


#endif
