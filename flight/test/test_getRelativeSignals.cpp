#include "../src/getRelativeSignals.h"

using namespace std;
int main () {

	// initialize value arrays
	float target[] = {0, 0, 0}, idealLoc[] = {0, 0, 0}, prevSignals[] = {0.5, 0.5, 0.5, 0.5};
	float skew = 0;

	// initialize vectors with arrays
	vector<float> t (target, target + sizeof(target) / sizeof(float));
	vector<float> i (idealLoc, idealLoc + sizeof(idealLoc) / sizeof(float));
	vector<float> p (prevSignals, prevSignals + sizeof(prevSignals) / sizeof(float));

	// welcome the tester
	cout << "You are testing the getRelativeSignals module." << endl
		 << "- You will be  prompted to enter the location (x, y, z) of the object you are tracking" << endl
		 << "- You will be given the relative output for yaw, pitch, roll, and throttle" << endl
		 << "- Drone is assumed to be at position [0, 0, 1] with existing signal values [0, 0, 0, 0.5]" << endl
		 << "- Drone wants to put the object at position [0, 0, 0] relative to itself" << endl
		 << "- All output values depend on the previous outputs (simulates moving object)" << endl
		 << "- Type 'quit' to exit at any time" << endl << endl
		 << "Press <enter> to continue...";
	cin.ignore();

	while (1) {
		// gather object location data
		cout << endl;
		cout << "Object X position: ";
		cin >> t[0];

		cout << endl;
		cout << "Object Y position: ";
		cin >> t[1];

		cout << endl;
		cout << "Object Z position: ";
		cin >> t[2];

		cout << endl << endl;

		vector<float> out = getRelativeSignals(t, skew, i);
		p = out;

		cout << "Yaw: " << out[0] << endl 
			 << "Pitch: " << out[1] << endl 
			 << "Roll: " << out[2] << endl 
		 	 << "Throttle: " << out[3] << endl;
	}
	
	return 0;
}
