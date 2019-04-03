#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    camara.setDeviceID(1);
    camara.initGrabber(1280,720);
    
    colors.setup(ofVec2f(1280, 720), 30);
}

//--------------------------------------------------------------
void ofApp::update(){
    camara.update();
    if (camara.isFrameNew()) {
        colors.addFrame(&camara);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    //camara.draw(0, 0);
    
    colors.getTextureReference().draw(0, 0);
    colors.drawGui();

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
