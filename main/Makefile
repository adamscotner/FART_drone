
INCLUDE	= -I/usr/local/include
LDFLAGS	= -L/usr/local/lib
LDLIBS	= -lwiringPi -lwiringPiDev -lpthread -lm -lwiringPiPca9685 -lraspicam -lraspicam_cv
# OPENCV command prints LDFLAGS and INCLUDE string
OPENCV = `pkg-config --cflags --libs opencv`

PWMChannel: ../flight/src/PWMChannel.h ../flight/src/PWMChannel.cpp
	g++ ../flight/src/$@.cpp -Wall $(INCLUDE) -c -o bin/$@.o

SignalGeneration: ../flight/src/SignalGeneration.cpp ../flight/src/SignalGeneration.h
	g++ ../flight/src/$@.cpp -Wall $(INCLUDE) -c -o bin/$@.o

objectDetection: ../obj_detect/objectDetection.cpp ../obj_detect/objectDetection.h
	g++ ../obj_detect/$@.cpp -Wall $(INCLUDE) -c -o bin/$@.o

FART: PWMChannel objectDetection SignalGeneration main.cpp
	g++ main.cpp bin/PWMChannel.o bin/SignalGeneration.o bin/objectDetection.o $(OPENCV) $(LDLIBS) -o bin/$@

clean: 
	rm bin/*