#include "objectDetection.h"

/// **************************************************************************************************************** ///
/// CONSTRUCTOR / DESTRUCTOR
/// **************************************************************************************************************** ///


// TODO: consider moving unsafe computations out of constructor
objectDetection::objectDetection()
{
	CascadeClassifier face_cascade;
	CascadeClassifier prof_face_cascade;
	face_cascades.push_back(face_cascade);
	face_cascades.push_back(prof_face_cascade);

	String face_cascade_name = "haarcascade_frontalface_alt.xml";
	String face_cascade_name_4 = "haarcascade_profileface.xml";
	window_name = "Capture - Face detection";

	face_types.push_back(faces);
	face_types.push_back(prof_faces);

	position.resize(3);
	
    //-- 1. Load the cascades
    if( !face_cascades[0].load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); };
	if( !face_cascades[1].load( face_cascade_name_4 ) ){ printf("--(!)Error loading profile face cascade\n"); };
}

// destructor
objectDetection::~objectDetection() {
	
}

int main( void )
{
	objectDetection vision_module;
	vision_module.initiateVisionModule();

	while(true)
	{
		vision_module.detectAndDisplay();

		int c = waitKey(10);
        if( (char)c == 27 ) { break; } // escape
	}

    return 0;
}

void objectDetection::initiateVisionModule()
{
	test = 1;//set to non-zero value to show camera / position output

	Camera.set( CV_CAP_PROP_FORMAT, CV_8UC3 );
    cout<<"Opening Camera..."<<endl;
    if (!Camera.open()) {cerr<<"Error opening the camera"<<endl;}
}

std::vector<float> objectDetection::detectAndDisplay()
{
	Mat frame;

	Camera.grab();
    Camera.retrieve (frame);

	if( frame.empty() )
    {
		printf(" --(!) No captured frame -- !");
    }

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
	}
	return position;
}