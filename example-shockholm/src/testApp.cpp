#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	ofSetFullscreen(true);
	ofEnableNormalizedTexCoords();
	ofDisableArbTex();
	
	cam.setDeviceID(0);
	cam.initGrabber(CAMERA_WIDTH, CAMERA_HEIGHT);
	cam.setupControls(ofxUVCQTKitVideoGrabber::LOGITECH_C910);
	cam.setupGui("Camera", "camera.xml");
	
	colorsOfMovement.setup(ofVec2f(CAMERA_WIDTH, CAMERA_HEIGHT), 60);
	
	ofVec2f size(CAMERA_WIDTH, CAMERA_HEIGHT);
	ofRectangle subsection(ofPoint(0.0,0.0), ofPoint(1.0,1.0));
    ofPoint corners[4];
    corners[0].x = 0;
    corners[0].y = 0;
    corners[1].x = OUTPUT_WIDTH;
    corners[1].y = 0;
    corners[2].x = OUTPUT_WIDTH;
    corners[2].y = OUTPUT_HEIGHT;
    corners[3].x = 0;
    corners[3].y = OUTPUT_HEIGHT;
    string name = "Warp/Blend";
    float guiWidth = 250;
    float guiHeight = 15;
    controller.setup(&(colorsOfMovement.getTextureReference()), size, subsection, corners, name, guiWidth, guiHeight);
	
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
	maskXSlider->setup("x", 0.0, 0.0, OUTPUT_WIDTH);
	maskXSlider->addListener(this, &testApp::onGuiChange);
	gui.add(maskXSlider);
	
	ofxFloatSlider * maskYSlider = new ofxFloatSlider();
	maskYSlider->setup("y", 0.0, 0.0, OUTPUT_HEIGHT);
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
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);
	controller.draw();
	
	ofSetColor(0);
	ofCircle(maskX, maskY, maskSize);
	
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
	maskX = gui.getFloatSlider("x");
	maskY = gui.getFloatSlider("x");
}