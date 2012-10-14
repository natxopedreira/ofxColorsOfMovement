#pragma once

#include "ofMain.h"
#include "ofxColorsOfMovement.h"
#include "ofxGlWarper.h"
#include "ofxUVCQTKitVideoGrabber.h"
#include "ofxGui.h"
#include "ofxXmlSettings.h"

#define OUTPUT_WIDTH 1920
#define OUTPUT_HEIGHT 1080
#define CAMERA_WIDTH 1280
#define CAMERA_HEIGHT 720

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
