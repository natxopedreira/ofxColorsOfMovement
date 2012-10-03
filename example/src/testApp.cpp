#include "testApp.h"

void testApp::setup(){	
	ofSetVerticalSync(true);
	ofBackground(0, 0, 0);
	ofSetFullscreen(true);
	
	cam.initGrabber(640,480);
	
	colorsOfMovement.setup(640, 480);
}

void testApp::update(){
	cam.update();
	
	if (cam.isFrameNew())
		colorsOfMovement.addFrame(&cam);
	
}

void testApp::draw(){
	colorsOfMovement.draw();
}
