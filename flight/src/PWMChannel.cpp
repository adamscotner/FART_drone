#include "PWMChannel.h"

PWMChannel::PWMChannel(){

	channel = 15;
	period = 19700;
	dutyTime = 1500;
	minDuty = 1250;
	maxDuty = 1750;
	sigScale = (float)(dutyTime - minDuty)/(maxDuty - minDuty);
	setDutyTime(dutyTime);

}
PWMChannel::PWMChannel(unsigned int channelSel, unsigned int period_us, unsigned int initDuty_us, unsigned int minDuty_us, unsigned int maxDuty_us){

	if(channelSel >= 0 && channelSel <= 15){
		channel = channelSel;
	}else{
		channel = 15;
	}
	period = period_us;
	if(minDuty_us <= maxDuty_us && minDuty_us < period_us && maxDuty_us <= period_us){
		minDuty = minDuty_us;
		maxDuty = maxDuty_us;
	}else{ //set to 5% of period if min/max input is invalid
		minDuty = maxDuty = 0.05 * period_us;
	}
	if(initDuty_us >= minDuty_us && initDuty_us <= maxDuty_us){
		dutyTime = initDuty_us;
		sigScale = (float)(dutyTime - minDuty)/(maxDuty - minDuty);
	}else{
		dutyTime = minDuty_us;
		sigScale = (float)(dutyTime - minDuty)/(maxDuty - minDuty);
	}
	setDutyTime(dutyTime);
}
unsigned int PWMChannel::getChannel(){
	return channel;
}
void PWMChannel::setChannel(unsigned int channelSel){
	if(channelSel >= 0 && channelSel <= 15){
		channel = channelSel;
	}
}
unsigned int PWMChannel::getPeriod(){
	return period;
}
unsigned int PWMChannel::getDutyTime(){
	return dutyTime;
}
void PWMChannel::setDutyTime(unsigned int duty_us){
	unsigned int dutyTicks = 0;
	if(duty_us >= minDuty && duty_us <= maxDuty){
		dutyTime = duty_us;
		dutyTicks = (unsigned int)(pwm_ch::maxPWM * dutyTime / period / 1.18 );
		/*printf("dutyTicks: %d\n", dutyTicks);
		printf("pinBase: %d\n", pwm_ch::pinBase);*/
		pwmWrite(pwm_ch::pinBase + channel, dutyTicks);
	}else{
		return;
	}
}
void PWMChannel::setDutyTimeTest(unsigned int duty_us){
	if(duty_us >= minDuty && duty_us <= maxDuty){
		dutyTime = duty_us;
	}else{
		return;
	}
}
void PWMChannel::setTempDutyTime(unsigned int duty_us, unsigned int duration_ms, unsigned int returnTo_us){
	setDutyTime(duty_us);
	delay(duration_ms);
	setDutyTime(returnTo_us);
}
/*void PWMChannel::setDutyFrom(int pin){
	
}*/
unsigned int PWMChannel::getMinDuty(){
	return minDuty;
}
unsigned int PWMChannel::getMaxDuty(){
	return maxDuty;
}
float PWMChannel::getSigScale(){
	return sigScale;
}
void PWMChannel::setSigScale(float relSignal){
	if(relSignal > 1 || relSignal < 0){
		return;
	}
	unsigned int relDuty = (unsigned int)(relSignal*(maxDuty - minDuty) + minDuty);
	setDutyTime(relDuty);
}
void PWMChannel::setSigScaleTest(float relSignal){
	if(relSignal > 1 || relSignal < 0){
		return;
	}
	unsigned int relDuty = (unsigned int)(relSignal*(maxDuty - minDuty) + minDuty);
	setDutyTimeTest(relDuty);
}
void PWMChannel::setTempSigScale(float relSignal, unsigned int duration_ms, float returnSig){
	if(relSignal > 1 || relSignal < 0 || returnSig > 1 || returnSig < 0){
		return;
	}
	setDutyTime(relSignal);
	delay(duration_ms);
	setDutyTime(returnSig);
}
/*
void PWMChannel::setSigScaleFrom(int pin){

}*/
PWMChannel::~PWMChannel(){
	//empty
}

// coordinates-to-relative signals functionality

void PWMChannel::print()
{
	std::cout << std::setw(5) << channel << " | "
		 << dutyTime << std::endl;
}