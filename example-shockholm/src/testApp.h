#pragma once

#include "ofMain.h"
#include "ofxColorsOfMovement.h"
#include "ofxGlWarper.h"
#include "ofxUVCQTKitVideoGrabber.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"

class testApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void onGuiChange(float & value);
	
	ofxColorsOfMovement colorsOfMovement;
	ofxGLWarper warper;
	ofxUVCQTKitVideoGrabber cam;
	
	ofxPanel gui;
	
	ofxXmlSettings settings;
	int camId;
	ofVec2f captureSize;
	ofVec2f outputSize;
	ofVec2f outputPosition;
	
	float maskSize;
	ofVec2f maskPosition;
	
	bool enableAppGui;
	bool enableColorsOfMovementGui;
	bool enableCameraGui;
	bool enableWarpGui;
	bool showMouse;
};
