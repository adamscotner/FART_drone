#include "pca9685.h"

#include <wiringPi.h> 
#include <wiringPiI2C.h>

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

//Raspberry Pi Port Only
#include <raspicam/raspicam_cv.h>
#include "opencv2/photo.hpp"
#include "opencv2/core.hpp"

#include <time.h>

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