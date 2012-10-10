#pragma once

#include "ofMain.h"
#include "ofxColorsOfMovement.h"

class testApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	
	ofxColorsOfMovement colorsOfMovement;
	ofVideoGrabber cam;
};
