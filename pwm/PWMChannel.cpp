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
PWMChannel::PWMChannel(int channelSel, int period_us, int initDuty_us, int minDuty_us, int maxDuty_us){

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
int PWMChannel::getChannel(){
	return channel;
}
void PWMChannel::setChannel(int channelSel){
	if(channelSel >= 0 && channelSel <= 15){
		channel = channelSel;
	}
}
int PWMChannel::getPeriod(){
	return period;
}
int PWMChannel::getDutyTime(){
	return dutyTime;
}
void PWMChannel::setDutyTime(int duty_us){
	int dutyTicks = 0;
	if(duty_us >= minDuty && duty_us <= maxDuty){
		dutyTime = duty_us;
		dutyTicks = (int)(pwm_ch::maxPWM * dutyTime / period / 1.18 );
		/*printf("dutyTicks: %d\n", dutyTicks);
		printf("pinBase: %d\n", pwm_ch::pinBase);*/
		pwmWrite(pwm_ch::pinBase + channel, dutyTicks);
	}else{
		return;
	}
}
void PWMChannel::setTempDutyTime(int duty_us, int duration_ms, int returnTo_us){
	setDutyTime(duty_us);
	delay(duration_ms);
	setDutyTime(returnTo_us);
}
void PWMChannel::setDutyFrom(int pin){
	
}
int PWMChannel::getMinDuty(){
	return minDuty;
}
int PWMChannel::getMaxDuty(){
	return maxDuty;
}
float PWMChannel::getSigScale(){
	return sigScale;
}
void PWMChannel::setSigScale(float relSignal){

}
void PWMChannel::setTempSigScale(float relSignal, int duration_ms, float returnSig){

}
void PWMChannel::setSigScaleFrom(int pin){

}
PWMChannel::~PWMChannel(){
	//empty
}