#pragma once

#include "ofMain.h"
#include "ofxColorsOfMovement.h"
#include "ofxWarpBlendTool.h"
#include "ofxGui.h"

class testApp : public ofBaseApp{
public:
	void setup();
	void update();
	void draw();
	
	void onGuiIntChange(int & v);
	void onGuiFloatChange(float & v);
	
	ofxColorsOfMovement colorsOfMovement;
	ofxWarpBlendTool::Controller controller;
	
	ofVideoGrabber cam;
	ofxPanel gui;
};
