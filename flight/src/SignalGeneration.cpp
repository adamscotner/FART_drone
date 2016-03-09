#include "SignalGeneration.h"

SignalGeneration::SignalGeneration () 
{
	// set up pwm driver
	int fd;
	//int ch = 8;
	const float period = 19.7;
	//int PWMresult = 0;
	//int werror;

	//Initialize Adafruit Driver
	try{
		fd = pca9685Setup(pwm_ch::pinBase, 0x40, 1/period);
		if(fd < 0){
			throw -1;
		}

	}
	catch (int e){
		printf("Error in PWM setup: %d\n", e);
	}

	//Clear all channels
	pca9685PWMReset(fd);

	double posArray[] = {0, 0, 0};
	targetPosition.assign(posArray, posArray + sizeof(posArray));

	// distance after which maximum power will be applied
	maxPowerThresh = 0.1;
	// percentage of maximum power to apply in any direction
	maxPower = 0.1;

	// PWMChannel *channel[5];
	signals.push_back(PWMChannel(3, 19700, 1500, 1079, 1908)); // yaw
	signals.push_back(PWMChannel(1, 19700, 1500, 1250, 1750)); // pitch
	signals.push_back(PWMChannel(0, 19700, 1500, 1250, 1750)); // roll/aileron
	signals.push_back(PWMChannel(2, 19700, 1092, 1090, 1917)); // throttle
	signals.push_back(PWMChannel(4, 19700, 1883, 1051, 1883)); // aux

}

// 
void SignalGeneration::newObjectPosition (double newPos[])
{
	prevObjectPosition = objectPosition;
	objectPosition.assign(newPos, newPos + sizeof(newPos));
}

void SignalGeneration::assignSignals (double newPos[])
{
	newObjectPosition(newPos);
	assignSignals();
}

void SignalGeneration::assignSignals (std::vector<double> newPosVec)
{
	double* newPos = &newPosVec[0];

	newObjectPosition(newPos);
	assignSignals();
}

void SignalGeneration::assignSignals ()
{

	// calc Yaw
	// nothing here yet. takes into account skew

	// calc Pitch, Roll, and Throttle
	calculateNewSignal(0, 2); // calc x->roll
	calculateNewSignal(1, 3); // calc y->throttle
	calculateNewSignal(2, 1); // calc z->pitch

	// print for testing
	print();
}

void SignalGeneration::calculateNewSignal (int posIdx, int signalIdx)
{
	// if the object is beyond the max power threshold, max out relative signals
	if (fabs(objectPosition[posIdx]) > maxPowerThresh) 
	{
		objectPosition[posIdx] > 0 
			? signals[signalIdx].setSigScale(0.5 + 0.5 * maxPower) 
			: signals[signalIdx].setSigScale(0.5 - 0.5 * maxPower);
	}
	else
	{
		// here's where we take last signal into account
		double relSig = objectPosition[posIdx] * (1 / maxPowerThresh);
		relSig = (relSig / 2) + 0.5;

		signals[signalIdx].setSigScale(relSig);
	}
}

void SignalGeneration::print()
{
	std::cout << "[ "
			  << objectPosition[0] << ", "
			  << objectPosition[1] << ", "
			  << objectPosition[2] << " ]"
			  << std::endl;

	for (int i = 0; i < 4; i++) {
		signals[i].print();
	}

	std::cout << std::endl;
}