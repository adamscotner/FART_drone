#ifndef OBJECTDETECTION_H
#define OBJECTDETECTION_H

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <raspicam/raspicam_cv.h>
#include "opencv2/photo.hpp"
#include "opencv2/core.hpp"

#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std;
using namespace cv;

// Global variables
vector<float> position(3);
short test;
vector<CascadeClassifier> face_cascades;
String window_name;

//Detect and displayes a face within a given frame;
//Return the face position;
vector<float> detectAndDisplay(Mat frame );

int setUpDetectionModule();

#endif