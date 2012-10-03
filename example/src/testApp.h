#pragma once

#include "ofMain.h"
#include "ColorsOfMovement.h"

class testApp : public ofBaseApp{
public:
	
	void setup();
	void update();
	void draw();
	
	ofVideoGrabber cam;
	ColorsOfMovement colorsOfMovement;
};