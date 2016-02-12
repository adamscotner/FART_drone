
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"

#include <iostream>
#include <stdio.h>
#include <time.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );
std::vector<float> getRelativePosition();

/** Global variables */
std::vector<float> position(3);
short test;

String face_cascade_name = "haarcascade_frontalface_alt.xml";
String face_cascade_name_4 = "haarcascade_profileface.xml";
//String face_cascade_name_2 = "haarcascade_frontalface_alt2.xml";
//String face_cascade_name_3 = "haarcascade_frontalface_default.xml";
//String eye_cascade_name = "haarcascade_eye.xml";
//String eyes_cascade_name = "haarcascade_eye_tree_eyeglasses.xml";
//String left_eye_cascade_name = "haarcascade_lefteye_2splits.xml";
//String right_eye_cascade_name = "haarcascade_righteye_2splits.xml";
//CascadeClassifier eyes_cascade;
CascadeClassifier face_cascade;
CascadeClassifier prof_face_cascade;
String window_name = "Capture - Face detection";

/** @function main */

int main( void )
{
	test = 1;//set to non-zero value to show camera / position output

    VideoCapture capture(0);
    Mat frame;
	
    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
	if( !prof_face_cascade.load( face_cascade_name_4 ) ){ printf("--(!)Error loading profile face cascade\n"); return -1; };
    //if( !eyes_cascade.load( eye_cascade_name ) ){ printf("--(!)Error loading eyes cascade\n"); return -1; };

    //-- 2. Read the video stream
    //capture.open( -1 );
    //if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }

	if( !capture.isOpened() )
        throw "Error when reading steam_avi";

    while ( capture.read(frame) )
    {
        if( frame.empty() )
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 3. Apply the classifier to the frame
		detectAndDisplay( frame );
		getRelativePosition();

        int c = waitKey(10);
        if( (char)c == 27 ) { break; } // escape
    }
    return 0;
}

std::vector<float> getRelativePosition()
{
	if(test){
		printf("Pos0: %f; Pos1: %f; Pos2: %f;\n", position[0], position[1], position[2]);
	}
	return position;
}

/** @function detectAndDisplay */

void detectAndDisplay( Mat frame )
{
    std::vector<Rect> faces;
	std::vector<Rect> prof_faces;
    Mat frame_gray;

	position[0] = position[1] = position[2] = 0.0;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

	if(faces.size() > 0)
	{
		for ( size_t i = 0; i < faces.size(); i++ )
		{
			Point center( faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2 );
			ellipse( frame, center, Size( faces[i].width/2, faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
		
			if(i == 0)//Return position of one face.
			{
				position[0] = (((faces[i].x + faces[i].width/2) / ((float)frame_gray.size().width)) - 0.5) * 2;//Relative position between -1 and +1
				position[1] = (((faces[i].y + faces[i].height/2) / ((float)frame_gray.size().height)) - 0.5) * 2;//Relative position between -1 and + 1
				position[2] = (((faces[i].width * faces[i].height) / ((float)frame_gray.size().width * frame_gray.size().height * 0.35)) - 0.5) * 2;//Relative position between -1 and +1
			}
	
			/*Mat faceROI = frame_gray( faces[i] );
			std::vector<Rect> eyes;

			//-- In each face, detect eyes
			eyes_cascade.detectMultiScale( faceROI, eyes, 1.1, 2, 0 |CASCADE_SCALE_IMAGE, Size(30, 30) );

			for ( size_t j = 0; j < eyes.size(); j++ )
			{
				Point eye_center( faces[i].x + eyes[j].x + eyes[j].width/2, faces[i].y + eyes[j].y + eyes[j].height/2 );
				int radius = cvRound( (eyes[j].width + eyes[j].height)*0.25 );
				circle( frame, eye_center, radius, Scalar( 255, 0, 0 ), 4, 8, 0 );
			}*/
			//printf("Pos0: %f; Pos1: %f; Pos2: %f;\n", position[0], position[1], position[2]);
		}
	}
	else{
		prof_face_cascade.detectMultiScale( frame_gray, prof_faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );
		for ( size_t i = 0; i < prof_faces.size(); i++ )
		{
			Point center( prof_faces[i].x + prof_faces[i].width/2, prof_faces[i].y + prof_faces[i].height/2 );
			ellipse( frame, center, Size( prof_faces[i].width/2, prof_faces[i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
		
			if(i == 0)//Return position of one face.
			{
				position[0] = (((prof_faces[i].x + prof_faces[i].width/2) / ((float)frame_gray.size().width)) - 0.5) * 2;//Relative position between -1 and +1
				position[1] = (((prof_faces[i].y + prof_faces[i].height/2) / ((float)frame_gray.size().height)) - 0.5) * 2;//Relative position between -1 and + 1
				position[2] = (((prof_faces[i].width * prof_faces[i].height) / ((float)frame_gray.size().width * frame_gray.size().height)) - 0.5) * 2;//Relative position between -1 and +1
			}
			//printf("Pos0: %f; Pos1: %f; Pos2: %f;\n", position[0], position[1], position[2]);
		}
	}
    //-- Show what you got
	if(test){
		imshow( window_name, frame );
	}
}