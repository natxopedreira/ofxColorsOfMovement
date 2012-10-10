#include "testApp.h"

void testApp::setup(){
	cam.initGrabber(640, 480);
	
	colorsOfMovement.setup(ofVec2f(640,480), 30);
	
	gui.setup("Colors of Movement");
	
	ofxLabel * mixLabel = new ofxLabel();
	mixLabel->setup("Channel Mixer", "Channel Mixer", 200, 40);
	gui.add(mixLabel);
	
	ofxIntSlider * bufferSize = new ofxIntSlider("Buffer Size", 30, 1, 300);
	bufferSize->addListener(this, &testApp::onGuiIntChange);
	gui.add(bufferSize);
	
	ofxFloatSlider * red = new ofxFloatSlider("Red Position", 0, 0, 1);
	red->addListener(this, &testApp::onGuiFloatChange);
	gui.add(red);
	
	ofxFloatSlider * green = new ofxFloatSlider("Green Position", 0, 0, 1);
	green->addListener(this, &testApp::onGuiFloatChange);
	gui.add(green);
	
	ofxFloatSlider * blue = new ofxFloatSlider("Blue Position", 0, 0, 1);
	blue->addListener(this, &testApp::onGuiFloatChange);
	gui.add(blue);
	
	
	ofxLabel * preLabel = new ofxLabel();
	preLabel->setup("Pre Effects", "Pre Effects", 200, 40);
	gui.add(preLabel);
	
	ofxFloatSlider * pre_gamma = new ofxFloatSlider("Pre Gamma", 1, 0, 5);
	pre_gamma->addListener(this, &testApp::onGuiFloatChange);
	gui.add(pre_gamma);
	
	ofxFloatSlider * pre_brightness = new ofxFloatSlider("Pre Brightness", 1, 0, 5);
	pre_brightness->addListener(this, &testApp::onGuiFloatChange);
	gui.add(pre_brightness);
	
	ofxFloatSlider * pre_saturation = new ofxFloatSlider("Pre Saturation", 1, 0, 5);
	pre_saturation->addListener(this, &testApp::onGuiFloatChange);
	gui.add(pre_saturation);
	
	ofxFloatSlider * pre_contrast = new ofxFloatSlider("Pre Contrast", 1, 0, 5);
	pre_contrast->addListener(this, &testApp::onGuiFloatChange);
	gui.add(pre_contrast);
	
	ofxFloatSlider * pre_hueShift = new ofxFloatSlider("Pre Hue Shift", 0, -1, 1);
	pre_hueShift->addListener(this, &testApp::onGuiFloatChange);
	gui.add(pre_hueShift);
	
	ofxLabel * postLabel = new ofxLabel();
	postLabel->setup("Post Effects", "Post Effects", 200, 40);
	gui.add(postLabel);
	
	ofxFloatSlider * post_gamma = new ofxFloatSlider("Post Gamma", 1, 0, 5);
	post_gamma->addListener(this, &testApp::onGuiFloatChange);
	gui.add(post_gamma);
	
	ofxFloatSlider * post_brightness = new ofxFloatSlider("Post Brightness", 1, 0, 5);
	post_brightness->addListener(this, &testApp::onGuiFloatChange);
	gui.add(post_brightness);
	
	ofxFloatSlider * post_saturation = new ofxFloatSlider("Post Saturation", 1, 0, 5);
	post_saturation->addListener(this, &testApp::onGuiFloatChange);
	gui.add(post_saturation);
	
	ofxFloatSlider * post_contrast = new ofxFloatSlider("Post Contrast", 1, 0, 5);
	post_contrast->addListener(this, &testApp::onGuiFloatChange);
	gui.add(post_contrast);
	
	ofxFloatSlider * post_hueShift = new ofxFloatSlider("Post Hue Shift", 0, -1, 1);
	post_hueShift->addListener(this, &testApp::onGuiFloatChange);
	gui.add(post_hueShift);
	
}

void testApp::update(){
	cam.update();
	if(cam.isFrameNew()){
		colorsOfMovement.addFrame(&cam);
	}
}

void testApp::draw(){
	colorsOfMovement.getTextureReference().draw(0,0);
	gui.draw();
	ofDrawBitmapString(ofToString(ofGetFrameRate()), 20,20);
}

void testApp::onGuiIntChange(int & value){
	colorsOfMovement.setBufferSize(gui.getIntSlider("Buffer Size"));	
}

void testApp::onGuiFloatChange(float & value){
	colorsOfMovement.setRPosition(gui.getFloatSlider("Red Position"));
	colorsOfMovement.setGPosition(gui.getFloatSlider("Green Position"));
	colorsOfMovement.setBPosition(gui.getFloatSlider("Blue Position"));
	
	colorsOfMovement.setPreGamma(gui.getFloatSlider("Pre Gamma"));
	colorsOfMovement.setPreBrightness(gui.getFloatSlider("Pre Brightness"));
	colorsOfMovement.setPreSaturation(gui.getFloatSlider("Pre Saturation"));
	colorsOfMovement.setPreContrast(gui.getFloatSlider("Pre Contrast"));
	colorsOfMovement.setPreHueShift(gui.getFloatSlider("Pre Hue Shift"));
	
	colorsOfMovement.setPostGamma(gui.getFloatSlider("Post Gamma"));
	colorsOfMovement.setPostBrightness(gui.getFloatSlider("Post Brightness"));
	colorsOfMovement.setPostSaturation(gui.getFloatSlider("Post Saturation"));
	colorsOfMovement.setPostContrast(gui.getFloatSlider("Post Contrast"));
	colorsOfMovement.setPostHueShift(gui.getFloatSlider("Post Hue Shift"));
}

