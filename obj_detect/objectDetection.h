

#ifndef OBJECTDETECTION_H
#define OBJECTDETECTION_H

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

//Raspberry Pi Port Only
//#include <raspicam/raspicam_cv.h>
//#include "opencv2/photo.hpp"
//#include "opencv2/core.hpp"

#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std;
using namespace cv;

class objectDetection {

//Detect and displayes a face within a given frame;
//Return the face position;
public:
	objectDetection();

	~objectDetection();

	//set the debug variable non-zero value to show camera / position output
	void initiateVisionModule(short debug);

	std::vector<float> detectAndDisplay();

private:

	// Global variables
	vector<CascadeClassifier> face_cascades;
	vector<float> position;
	String window_name;
	short test;

	//PC Port
	VideoCapture capture;

	//Raspberry Pi Port
	//raspicam::RaspiCam_Cv Camera;

	vector<Rect> faces;
	vector<Rect> prof_faces;
	vector< vector<Rect> > face_types;
};
#endif

