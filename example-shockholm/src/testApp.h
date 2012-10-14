#pragma once

#include "ofMain.h"
#include "ofxColorsOfMovement.h"
#include "ofxWarpBlendTool.h"
#include "ofxUVCQTKitVideoGrabber.h"
#include "ofxGui.h"

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
	ofxWarpBlendTool::Controller controller;
	ofxUVCQTKitVideoGrabber cam;
	
	ofxPanel gui;
	
	float maskSize, maskY, maskX;
	
	bool enableAppGui;
	bool enableColorsOfMovementGui;
	bool enableCameraGui;
	bool enableWarpBlendGui;
};
