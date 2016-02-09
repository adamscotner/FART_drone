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
	PWMChannel();
	PWMChannel(int channelSel, int period_us, int initDuty_us, int minDuty_us, int maxDuty_us);
	int getChannel();
	void setChannel(int channelSel);
	int getPeriod();
	//void setPeriod(int period_us);
	int getDutyTime();
	void setDutyTime(int duty_us);
	void setTempDutyTime(int duty_us, int duration_ms, int returnTo_us);
	void setDutyFrom(int pin);
	int getMinDuty();
	//void setMinDuty(int min_us);
	int getMaxDuty();
	//void setMaxDuty(int max_us);
	float getSigScale();
	void setSigScale(float relSignal);
	void setTempSigScale(float relSignal, int duration_ms, float returnSig);
	void setSigScaleFrom(int pin);
	~PWMChannel();

private:
	int channel;
	int period;
	int dutyTime;
	int minDuty;
	int maxDuty;
	float sigScale;
};

#endif 
/*PWMCHANNEL_H*/