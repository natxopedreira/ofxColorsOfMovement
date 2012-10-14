#include "testApp.h"

void testApp::setup(){
	cam.initGrabber(640, 480);
	colorsOfMovement.setup(ofVec2f(640,480), 30);
}

void testApp::update(){
	cam.update();
	if(cam.isFrameNew()){
		colorsOfMovement.addFrame(&cam);
	}
}

void testApp::draw(){
	colorsOfMovement.getTextureReference().draw(0,0);
	colorsOfMovement.drawGui();
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 20,20);
}