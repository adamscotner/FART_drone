/* PWMChannel: This class is used to drive and read the 16 channel Adafruit PWM driver
*	Required Libraries: 
*	wiringPiPca9685 (https://github.com/Reinbert/pca9685)
*	wiringPi (http://wiringpi.com/download-and-install/)
*	
*
*/
#include "pca9685.h"

#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>

#ifndef PWMCHANNEL_H
#define PWMCHANNEL_H

namespace pwm_ch{
	const int pinBase = 300;
	const int maxPWM = 4096;
}

class PWMChannel{
public:
	PWMChannel(); 															//Default constructor
	PWMChannel(unsigned int channelSel, unsigned int period_us, unsigned int initDuty_us, unsigned int minDuty_us, unsigned int maxDuty_us);
	unsigned int getChannel(); 														//returns channel number assigned
	void setChannel(unsigned int channelSel); 										//sets/reassigns channel
	unsigned int getPeriod(); 														//returns set period
	//void setPeriod(int period_us);
	unsigned int getDutyTime(); 														//returns active duty time
	void setDutyTime(unsigned int duty_us); 											//sets active duty time
	void setTempDutyTime(unsigned int duty_us, unsigned int duration_ms, unsigned int returnTo_us);	//sets active duty time for duration_ms then sets back to returnTo_us
	//void setDutyFrom(int pin);
	unsigned int getMinDuty();														//returns minimum duty time
	//void setMinDuty(int min_us);
	unsigned int getMaxDuty();														//returns maximum duty time
	//void setMaxDuty(int max_us);
	float getSigScale();													//get the 0..1 value of duty time
	void setSigScale(float relSignal);										//set the 0..1 value of duty time
	void setTempSigScale(float relSignal, unsigned int duration_ms, float returnSig);//set the 0..1 value of duty time for duration_ms
	//void setSigScaleFrom(int pin);
	~PWMChannel();															//Destructor

private:
	unsigned int channel;
	unsigned int period;
	unsigned int dutyTime;
	unsigned int minDuty;
	unsigned int maxDuty;
	float sigScale;
};

#endif 
/*PWMCHANNEL_H*/