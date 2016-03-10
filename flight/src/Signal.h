#ifndef SIGNAL_H
#define SIGNAL_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip> 

/*
	Signal class
	-holds relative signal value
	-holds discrete PWN value (duty time)
*/

class Signal 
{
	private:
		// value 0 to 1, relative to max and min duty time
		double relativeSignal;
		// actual duty time in microseconds
		int dutyTime;
		// maximum signal duty time, microseconds
		int maxDutyTime;
		// minimum signal duty time, microseconds
		int minDutyTime;

		// calculate duty time from 
		// void getDutyTime();
		void setDutyTime() 
		{
			double signalRange = maxDutyTime - minDutyTime;
			int signalDiff = (int) ( signalRange * relativeSignal );
			dutyTime = minDutyTime + signalDiff;
		}

	public:
		// constructor
		Signal (double _relativeSignal, int _maxDutyTime, int _minDutyTime);
		Signal ();

		double getRelSig();
		void setSigData(double newval);
		int getDisSig();

		void print();
};

#endif