#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	//ofSetFullscreen(true);
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
	
	ofSetWindowPosition(outputPosition.x, outputPosition.y);
	
	
	cam.setDeviceID(camId);
	cam.initGrabber(captureSize.x, captureSize.y);
	cam.setupControls(ofxUVCQTKitVideoGrabber::LOGITECH_C910);
	cam.setupGui("Camera", "camera.xml");
	
	colorsOfMovement.setup(captureSize/2, 30);

	warper.setup(0, 0, captureSize.x, captureSize.y);
	warper.load();

	enableAppGui = false;
	enableColorsOfMovementGui = false;
	enableCameraGui = false;
	enableWarpGui = false;
	showMouse = false;

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
			//ofExit();
		}
	}
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255);
	warper.begin();
	colorsOfMovement.getTextureReference().draw(0,0,captureSize.x, captureSize.y);
	warper.end();
	
	ofSetColor(0);
	ofCircle(maskPosition, maskSize);
	
	if(enableColorsOfMovementGui) colorsOfMovement.drawGui();
	if(enableCameraGui) cam.drawGui();
	if(enableAppGui) {
		ofSetColor(255);
		ofDrawBitmapString(ofToString(ofGetFrameRate()), 20,20);
		gui.draw();
	}
	if (enableWarpGui) {
		warper.begin();
		ofPushStyle();
		ofSetColor(255);
		ofNoFill();
		ofRect(0, 0, captureSize.x, captureSize.y);
		ofPopStyle();
		warper.end();
	}
	if(showMouse){
		ofSetColor(255);
		ofLine(mouseX, 0, mouseX, ofGetHeight());
		ofLine(0, mouseY, ofGetWidth(), mouseY);
	}
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	if(key == ' ') ofToggleFullscreen();
	else if(key == '1') enableColorsOfMovementGui = !enableColorsOfMovementGui;
	else if(key == '2') enableCameraGui = !enableCameraGui;
	else if(key == '3') enableAppGui = !enableAppGui;
	else if(key == '4') {
		enableWarpGui = !enableWarpGui;
		if(enableWarpGui) warper.activate();
		else warper.deactivate();
		warper.save();
	}
	else if(key == 'm'){
		showMouse = !showMouse;
		if(showMouse){
			ofShowCursor();
		}
		else{
			ofHideCursor();
		}
	}
}

void testApp::onGuiChange(float & value){
	maskSize = gui.getFloatSlider("Size");
	maskPosition.set(gui.getFloatSlider("x"),
					 gui.getFloatSlider("y"));
}