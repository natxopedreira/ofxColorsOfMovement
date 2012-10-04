#pragma once

#include "ofMain.h"
#include "ofxColorsOfMovement.h"
#include "ofxGui.h"

class testApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	
	void onGuiIntChange(int & v);
	void onGuiFloatChange(float & v);
	
	ofxColorsOfMovement colorsOfMovement;
	ofVideoGrabber cam;
	ofxPanel gui;
};
