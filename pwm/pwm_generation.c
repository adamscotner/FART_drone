/*************************************************************************
 * servo.c
 *
 * PCA9685 servo example
 * Connect a servo to any pin. It will rotate to random angles.
 *
 *
 * This software is a devLib extension to wiringPi <http://wiringpi.com/>
 * and enables it to control the Adafruit PCA9685 16-Channel 12-bit
 * PWM/Servo Driver <http://www.adafruit.com/products/815> via I2C interface.
 *
 * Copyright (c) 2014 Reinhard Sprung
 *
 * If you have questions or improvements email me at
 * reinhard.sprung[at]gmail.com
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * The given code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You can view the contents of the licence at <http://www.gnu.org/licenses/>.
 **************************************************************************
 */

#include "pca9685.h"

#include <wiringPi.h>

#include <stdio.h>
#include <stdlib.h>

#define PIN_BASE 300
#define MAX_PWM 4096
#define HERTZ 50
#define MIN_DUTY 1.25 //in ms
#define MAX_DUTY 1.75 //in ms
#define PERIOD 19.7 //in ms

/**
 * Calculate the number of ticks the signal should be high for the required amount of time
 */
int calcTicks(float impulseMs, float period)
{
	//float cycleMs = 1000.0f / hertz;
	return (int)(MAX_PWM * impulseMs / period + 0.5f );
}

/**
 * input is [0..1]
 * output is [min..max]
 */
float map(float input, float min, float max)
{
	return (input * max) + (1 - input) * min;
}

void setPWMSignal(int channel, float period, float duty){
	int ticks = calcTicks(map(duty,MIN_DUTY,MAX_DUTY), 1/period);
	pwmWrite(PIN_BASE+channel, ticks);
	//delay(period*1000);
}

void printMenu(){
	printf("1. Set PWM signal\n"
		"2. Reset all channels \n");
}

int main(void)
{
	printf("PCA9685 User-defined signal generation for KK2\n");

	// Setup with pinbase 300 and i2c location 0x40
	int fd = pca9685Setup(PIN_BASE, 0x40, 1/PERIOD);
	if (fd < 0)
	{
		printf("Error in setup\n");
		return fd;
	}

	// Reset all output
	pca9685PWMReset(fd);
	
	int cmd = 1;
	float dutytime = MIN_DUTY;
	int dutyTicks = 0;
	int channel = 0;
	while(cmd != 0){
		printMenu();
		printf("Select an option: ");
		cmd = getchar()-'0';
		switch(cmd){
			case 1:
				printf("Select channel: ");
				getchar();
				channel = getchar()-'0';
				printf("Testing 1.25ms...\n");
				//setPWMSignal(channel, PERIOD, 0.0);
				dutytime = map(0, 1.0, 1.75);
				dutyTicks = calcTicks(dutytime, PERIOD);
				pwmWrite(PIN_BASE, dutyTicks);
				delay(2000);
				printf("Testing 1.50ms...\n");
				dutytime = map(0.5, 1.0, 1.75);
				//setPWMSignal(channel, PERIOD, 0.5);
				dutyTicks = calcTicks(dutytime, PERIOD);
                                pwmWrite(PIN_BASE, dutyTicks);
				delay(2000);
				printf("Testing 1.75ms...\n");
				dutytime = map(1, 1.0, 1.75);
				//setPWMSignal(channel, PERIOD, 1.0);
				dutyTicks = calcTicks(dutytime, PERIOD);
                                pwmWrite(PIN_BASE, dutyTicks);
				delay(2000);
			break;
			case 2:
			break;
			default:
			break;
		}
	}

	// Set servo to neutral position at 1.5 milliseconds
	// (View http://en.wikipedia.org/wiki/Servo_control#Pulse_duration)
	/*float millis = 1.5;
	int tick = calcTicks(millis, HERTZ);
	pwmWrite(PIN_BASE, tick);
	delay(2000);


	int active = 1;
	while (active)
	{
		// That's a hack. We need a random number < 1
		float r = rand() /(rand() * 10);
		//while (r > 1)
		//	r /= 10;
		printf("r: %lf\n", r);
		millis = map(r, 1.25, 1.75);
		printf("millis: %lf\n", millis);
		tick = calcTicks(millis, HERTZ);
		printf("tick: %d\n", tick);

		pwmWrite(PIN_BASE, tick);
		delay(1000);
	}*/

	return 0;
}
