#include "pca9685.h"

#include <wiringPi.h> 
#include <wiringPiI2C.h>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../flight/src/PWMChannel.h"
#include "../flight/src/SignalGeneration.h"
#include "../obj_detect/objectDetection.h"

//Prototypes
using namespace std;

int main() {
	//cout << "Hello World!" << endl;
	cout.precision(3);


	SignalGeneration sg;
	objectDetection vision_module;
	vector<double> pos;

	vision_module.initiateVisionModule(1);

	while(true)
	{
		pos = vision_module.detectAndDisplay();
		sg.assignSignals(pos);
		cin.ignore();
	}

    return 0;
}