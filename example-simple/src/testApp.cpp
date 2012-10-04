#include "testApp.h"

void testApp::setup(){	
	cam.initGrabber(640,480);
	
	colorsOfMovement.setup(ofRectangle(0,0,640,480), ofVec2f(640,480), 30);
	colorsOfMovement.setRIndex(0);
	colorsOfMovement.setGIndex(14);
	colorsOfMovement.setBIndex(29);
}

void testApp::update(){
	cam.update();
	
	if (cam.isFrameNew())
		colorsOfMovement.addFrame(&cam);
	
}

void testApp::draw(){
	colorsOfMovement.draw();
	ofDrawBitmapString(ofToString(ofGetFrameRate()),20,20);
}
