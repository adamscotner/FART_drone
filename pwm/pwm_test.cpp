#include "pca9685.h"

#include <wiringPi.h>
#include <wiringPiI2C.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "PWMChannel.h"

//Prototypes
using namespace std;

int main(int argc, char* argv[]){
	int fd;
	int ch = 8;
	const float period = 19.7;
	int PWMresult = 0;
	int werror;

	//Initialize Adafruit Driver
	try{
		fd = pca9685Setup(pwm_ch::pinBase, 0x40, 1/period);
		if(fd < 0){
			throw -1;
		}

	}
	catch (int e){
		printf("Error in PWM setup: %d\n", e);
		return e;
	}

	//Clear all channels
	pca9685PWMReset(fd);

	//Declaring objects
	PWMChannel ch_0(0, 19700, 1500, 1250, 1750);
	/*cout << "ch_0:\n"
		<< ch_0.getPeriod() << endl
		<< ch_0.getChannel() << endl
		<< ch_0.getDutyTime() << endl;
	pwmWrite(pwm_ch::pinBase + 0, 263);*/
	PWMChannel ch_1(1, 19700, 1500, 1250, 1750);
	PWMChannel ch_2(2, 19700, 1092, 1090, 1917);
	PWMChannel ch_3(3, 19700, 1500, 1079, 1908);
	PWMChannel ch_4(4, 19700, 1883, 1051, 1883);
	//PWMChannel ch_8(8, 19700, 1092, 1092, 1883);
	//pwmWrite(pwm_ch::pinBase + 8, 0);
	//werror = wiringPiI2CWriteReg16 (fd, pwm_ch::pinBase-4, 1792) ;

	//pca9685PWMReset(fd);

	for(int i=0; i<76; i++){
		//pca9685PWMRead(fd, 8, &PWMresult, NULL);
		//pwmWrite(pwm_ch::pinBase + ch, 263);
		//PWMresult = digitalRead(pwm_ch::pinBase + ch) & 0xFFF;
		//pca9685PWMRead(fd, ch, &PWMresult, 0);
		PWMresult = wiringPiI2CReadReg16(fd, pwm_ch::pinBase - 50 + i) & 0xFFF;
		//cout << "fd: " << fd << endl;
		//std::cout << "Channel "<<ch<<" PWM: " << PWMresult << std::flush;
		std::cout << "pinBase -50+" <<i<<" Signal: " << PWMresult << endl;
		//delay(100);
	}
	std::cout << std::endl;

	//Testing Channel 0-4 outputs


	return 0;
}