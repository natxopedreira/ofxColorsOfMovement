#pragma once

#include "ofMain.h"
#include "ofxColorsOfMovement.h"
#include "ofxWarpBlendTool.h"

class testApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	
	ofxColorsOfMovement colorsOfMovement;
	ofxWarpBlendTool::Controller controller;
	
	ofVideoGrabber cam;
};
