#ifndef OBJECTDETECTION_H
#define OBJECTDETECTION_H

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <time.h>

//Detect and displayes a face within a given frame;
std::vector<float> detectAndDisplay( cv::Mat frame );

#endif