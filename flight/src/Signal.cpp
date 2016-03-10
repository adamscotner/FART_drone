#include "Signal.h"

/*
	Signal class
	-holds relative signal value
	-holds discrete PWN value (duty time)
*/

Signal::Signal (double _relativeSignal, int _maxDutyTime, int _minDutyTime)
{
	relativeSignal = _relativeSignal;
	maxDutyTime = _maxDutyTime;
	minDutyTime = _minDutyTime;
	setDutyTime();
}

Signal::Signal () 
{
	relativeSignal = 0.5;
}

double Signal::getRelSig()
{
	return relativeSignal;
}

void Signal::setSigData(double newval)
{
	relativeSignal = newval;
	setDutyTime();
}

int Signal::getDisSig() 
{
	return dutyTime;
}

void Signal::print()
{
	std::cout << std::setw(5) << relativeSignal << " | "
		 << dutyTime << std::endl;
}