#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	ofSetFullscreen(true);
	ofEnableNormalizedTexCoords();
	ofDisableArbTex();
	
	settings.loadFile("settings.xml");
	camId = settings.getValue("camera", 0);
	captureSize.set(settings.getValue("capture:width", 1280),
					settings.getValue("capture:height", 720));
	outputSize.set(settings.getValue("output:width", 1080),
					settings.getValue("output:height", 1920));
	outputPosition.set(settings.getValue("output:x", 2000),
				   settings.getValue("output:y", 0));
	
	
	cam.setDeviceID(camId);
	cam.initGrabber(captureSize.x, captureSize.y);
	cam.setupControls(ofxUVCQTKitVideoGrabber::LOGITECH_C910);
	cam.setupGui("Camera", "camera.xml");
	
	colorsOfMovement.setup(captureSize, 60);
	
	ofRectangle subsection(ofPoint(0.0,0.0), ofPoint(1.0,1.0));
    ofPoint corners[4];
    corners[0].x = outputSize.x;
    corners[0].y = 0;
    corners[1].x = outputSize.x;
    corners[1].y = outputSize.y;
    corners[2].x = 0;
    corners[2].y = outputSize.y;
	corners[3].x = 0;
    corners[3].y = 0;
    string name = "Warp/Blend";
    float guiWidth = 250;
    float guiHeight = 15;
    controller.setup(&(colorsOfMovement.getTextureReference()), captureSize, subsection, corners, name, guiWidth, guiHeight);
	
	enableAppGui = false;
	enableColorsOfMovementGui = false;
	enableCameraGui = false;
	enableWarpBlendGui = false;
	

	gui.setup("App", "app.xml");
	
	ofxFloatSlider * maskSizeSlider = new ofxFloatSlider();
	maskSizeSlider->setup("Size", 0.0, 0.0, 100);
	maskSizeSlider->addListener(this, &testApp::onGuiChange);
	gui.add(maskSizeSlider);
	
	ofxFloatSlider * maskXSlider = new ofxFloatSlider();
	maskXSlider->setup("x", 0.0, 0.0, outputSize.x);
	maskXSlider->addListener(this, &testApp::onGuiChange);
	gui.add(maskXSlider);
	
	ofxFloatSlider * maskYSlider = new ofxFloatSlider();
	maskYSlider->setup("y", 0.0, 0.0, outputSize.y);
	maskYSlider->addListener(this, &testApp::onGuiChange);
	gui.add(maskYSlider);
	
	gui.loadFromFile("app.xml");
}

//--------------------------------------------------------------
void testApp::update(){
	cam.update();
	if(cam.isFrameNew()){
		colorsOfMovement.addFrame(&(cam.getTextureReference()));
	}
	
	// quit if screen size don't match
	if (ofGetFrameNum() % 300 == 299) {
		if(ofGetWidth() != outputSize.x || ofGetHeight() != outputSize.y){
			ofExit();
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);
	controller.draw();
	
	ofSetColor(0);
	ofCircle(maskPosition, maskSize);
	
	if(enableColorsOfMovementGui) colorsOfMovement.drawGui();
	if(enableCameraGui) cam.drawGui();
	if(enableWarpBlendGui) controller.drawGui();
	if(enableAppGui) {
		ofSetColor(255);
		ofDrawBitmapString(ofToString(ofGetFrameRate()), 20,20);
		gui.draw();
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == ' ') ofToggleFullscreen();
	else if(key == '1') enableColorsOfMovementGui = !enableColorsOfMovementGui;
	else if(key == '2') enableCameraGui = !enableCameraGui;
	else if(key == '3') enableWarpBlendGui = !enableWarpBlendGui;
	else if(key == '4') enableAppGui = !enableAppGui;
}

void testApp::onGuiChange(float & value){
	maskSize = gui.getFloatSlider("Size");
	maskPosition.set(gui.getFloatSlider("x"),
					 gui.getFloatSlider("y"));
}