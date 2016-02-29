#include "objectDetection.h"

using namespace std;
using namespace cv;

// Global variables
std::vector<float> position(3);
short test;

String face_cascade_name = "haarcascade_frontalface_alt.xml";
String face_cascade_name_4 = "haarcascade_profileface.xml";
std::vector<CascadeClassifier> face_cascades;
String window_name = "Capture - Face detection";

int main( void )
{
	test = 1;//set to non-zero value to show camera / position output

	CascadeClassifier face_cascade;
	CascadeClassifier prof_face_cascade;
	face_cascades.push_back(face_cascade);
	face_cascades.push_back(prof_face_cascade);

    VideoCapture capture(0);
    Mat frame;
	
    //-- 1. Load the cascades
    if( !face_cascades[0].load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
	if( !face_cascades[1].load( face_cascade_name_4 ) ){ printf("--(!)Error loading profile face cascade\n"); return -1; };
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

        int c = waitKey(10);
        if( (char)c == 27 ) { break; } // escape
    }
    return 0;
}

/** @function detectAndDisplay */

std::vector<float> detectAndDisplay( Mat frame )
{
    std::vector<Rect> faces;
	std::vector<Rect> prof_faces;
	std::vector< std::vector<Rect> > face_types;

	face_types.push_back(faces);
	face_types.push_back(prof_faces);

    Mat frame_gray;

	position[0] = position[1] = position[2] = 0.0;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

	for(int j = 0; j < 2; j++)
	{
		face_cascades[j].detectMultiScale( frame_gray, face_types[j], 1.1, 3, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

		//Circle and retrieve position of only one face;
		if(face_types[j].size() > 0)
		{
			//if(test)
			//	printf("The face type detected is: %i;\n", j);

			int i = 0;
			Point center( face_types[j][i].x + face_types[j][i].width/2, face_types[j][i].y + face_types[j][i].height/2 );
			ellipse( frame, center, Size( face_types[j][i].width/2, face_types[j][i].height/2 ), 0, 0, 360, Scalar( 255, 0, 255 ), 4, 8, 0 );
			position[0] = (((face_types[j][i].x + face_types[j][i].width/2) / ((float)frame_gray.size().width)) - 0.5) * 2;//Relative position between -1 and +1
			position[1] = (((face_types[j][i].y + face_types[j][i].height/2) / ((float)frame_gray.size().height)) - 0.5) * 2;//Relative position between -1 and + 1
			position[2] = (((face_types[j][i].width * face_types[j][i].height) / ((float)frame_gray.size().width * frame_gray.size().height * 0.35)) - 0.5) * 2;//Relative position between -1 and +1
			if(j == 0)//If frontal_face was detected do not attemt to detect a profile_face
				j++;
		}
	}
    //-- Show what you got
	if(test){
		imshow( window_name, frame );
		printf("Pos0: %f; Pos1: %f; Pos2: %f;\n", position[0], position[1], position[2]);
	}
	return position;
}