#include "testApp.h"

void testApp::setup(){
	ofEnableNormalizedTexCoords();
	ofDisableArbTex();
	
	cam.initGrabber(640, 480);
	
	colorsOfMovement.setup(ofVec2f(640,480), 30);
	
	ofVec2f size(cam.getWidth(), cam.getHeight());    
	ofRectangle subsection(ofPoint(0.0,0.0), ofPoint(1.0,1.0));
    ofPoint corners[4];
    corners[0].x = 0;
    corners[0].y = 0;
    corners[1].x = ofGetWidth();
    corners[1].y = 0;
    corners[2].x = ofGetWidth();
    corners[2].y = ofGetHeight();
    corners[3].x = 0;
    corners[3].y = ofGetHeight();
    string name = "Warp/Blend";
    float guiWidth = 250;
    float guiHeight = 15;
    controller.setup(&(colorsOfMovement.getTextureReference()), size, subsection, corners, name, guiWidth, guiHeight);
	
}

void testApp::update(){
	cam.update();
	if(cam.isFrameNew()){
		colorsOfMovement.addFrame(&cam);
	}
}

void testApp::draw(){
	controller.draw();
	controller.drawGui();
	colorsOfMovement.drawGui();
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 20,20);
}