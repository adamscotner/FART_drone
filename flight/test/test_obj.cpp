// #include "pca9685.h"

// #include <wiringPi.h> 
// #include <wiringPiI2C.h>

// #include <stdio.h>
// #include <stdlib.h>
// #include <iostream>
#include "../src/PWMChannel.h"
#include "../src/SignalGeneration.h"

//Prototypes
using namespace std;

int main(int argc, char* argv[]){
	// int fd;
	// int ch = 8;
	// const float period = 19.7;
	// int PWMresult = 0;
	// int werror;

	// //Initialize Adafruit Driver
	// try{
	// 	fd = pca9685Setup(pwm_ch::pinBase, 0x40, 1/period);
	// 	if(fd < 0){
	// 		throw -1;
	// 	}

	// }
	// catch (int e){
	// 	printf("Error in PWM setup: %d\n", e);
	// 	return e;
	// }

	// //Clear all channels
	// pca9685PWMReset(fd);

// using namespace std;
// int main () {

	std::cout.precision(3);

	SignalGeneration sg;

	double input1[] = { -0.6, 0.6, 0.99 };
	double input2[] = { -0.3, 0.48, 0.9 };
	double input3[] = { -0.2, 0.36, 0.45 };
	double input4[] = { -0.1, 0.24, 0.2 };
	double input5[] = { 0, 0, 0 };
	double input6[] = { 0, 0, 0 };
	double input7[] = { 0, 0, 0 };

	sg.assignSignals(input1);
	std::cin.ignore();
	sg.assignSignals(input2);
	std::cin.ignore();
	sg.assignSignals(input3);
	std::cin.ignore();
	sg.assignSignals(input4);
	std::cin.ignore();
	sg.assignSignals(input5);
	std::cin.ignore();
	sg.assignSignals(input6);
	std::cin.ignore();
	sg.assignSignals(input7);

	return 0;
}
