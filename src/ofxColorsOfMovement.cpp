#include "ofxColorsOfMovement.h"

ofxColorsOfMovement::ofxColorsOfMovement():
index(-1),
rIndex(0),
gIndex(0),
bIndex(0),
gamma(1.0),
brightness(1.0),
saturaion(1.0),
contrast(1.0),
tone(new float[9]),
isSetup(false)
{
	vbo.setMode(OF_PRIMITIVE_TRIANGLES);
	
	shader.setupShaderFromSource(GL_VERTEX_SHADER, OFXCM_VERTEX_SHADER);
	shader.setupShaderFromSource(GL_FRAGMENT_SHADER, OFXCM_FRAGMENT_SHADER);
	shader.linkProgram();
	
	tone[0] = 1.0;
	tone[1] = 0.0;
	tone[2] = 0.0;
	
	tone[3] = 0.0;
	tone[4] = 1.0;
	tone[5] = 0.0;

	tone[6] = 0.0;
	tone[7] = 0.0;
	tone[8] = 1.0;
}

void ofxColorsOfMovement::setup(ofRectangle rectangle, ofVec2f texureSize, unsigned int bufferSize){
	isSetup = true;
	
	setRectangle(rectangle);
	setTextureSize(texureSize, false);
	setBufferSize(bufferSize);
}

void ofxColorsOfMovement::addFrame(ofBaseDraws * frame){
	if(!isSetup || !buffer.size()) return;
	
	index ++;
	index = index % buffer.size();
	
	buffer[index]->begin();
	frame->draw(0, 0, texureSize.x, texureSize.y);
	buffer[index]->end();
	
	internalRIndex = index + rIndex;
	internalRIndex = internalRIndex % buffer.size();
	
	internalGIndex = index + gIndex;
	internalGIndex = internalGIndex % buffer.size();
	
	internalBIndex = index + bIndex;
	internalBIndex = internalBIndex % buffer.size();
}

void ofxColorsOfMovement::draw(){
	if(!isSetup || !buffer.size()) return;
	
	beginNormalized();
	
	shader.begin();
	
	shader.setUniformTexture("texR", buffer[internalRIndex]->getTextureReference(), 0 );
	shader.setUniformTexture("texG", buffer[internalGIndex]->getTextureReference(), 1 );
	shader.setUniformTexture("texB", buffer[internalBIndex]->getTextureReference(), 2 );
	shader.setUniform1f("gamma", gamma );
	shader.setUniform1f("brightness", brightness );
	shader.setUniform1f("saturation", saturaion );
	shader.setUniform1f("contrast", contrast );
	// there is no built in "setUniform" format3x3 in ofShader
	glUniformMatrix3fv(glGetUniformLocation(shader.getProgram(), "tone"), 1, GL_FALSE, tone);

	vbo.draw();
	
	shader.end();
	
	endNormalized();	
}

void ofxColorsOfMovement::setRectangle(ofRectangle rectangle){
	this->rectangle = rectangle;
	
	vbo.clearVertices();
	vbo.addVertex(ofPoint(rectangle.x,rectangle.y,0));
	vbo.addVertex(ofPoint(rectangle.x + rectangle.width,0,0));
	vbo.addVertex(ofPoint(rectangle.x,rectangle.y + rectangle.height,0));
	
	vbo.addVertex(ofPoint(rectangle.x,rectangle.y + rectangle.height,0));
	vbo.addVertex(ofPoint(rectangle.x + rectangle.width,rectangle.y,0));
	vbo.addVertex(ofPoint(rectangle.x + rectangle.width,rectangle.y + rectangle.height,0));
}
ofRectangle ofxColorsOfMovement::getRectangle(){
	return rectangle;
}

void ofxColorsOfMovement::setTextureSize(ofVec2f texureSize, bool reallocate){
	this->texureSize = texureSize;
	
	float coordWidth = (float)texureSize.x / ofNextPow2(texureSize.x);
	float coordHeight = (float)texureSize.y / ofNextPow2(texureSize.y);
	
	vbo.addTexCoord(ofVec2f(0,0));
	vbo.addTexCoord(ofVec2f(coordWidth,0));
	vbo.addTexCoord(ofVec2f(0,coordHeight));
	
	vbo.addTexCoord(ofVec2f(0,coordHeight));
	vbo.addTexCoord(ofVec2f(coordWidth,0));
	vbo.addTexCoord(ofVec2f(coordWidth,coordHeight));
	
	if(reallocate) allocate();
}
ofVec2f ofxColorsOfMovement::getTextureSize(){
	return texureSize;
}


void ofxColorsOfMovement::setBufferSize(unsigned int bufferSize) {
	index = -1;
	this->bufferSize = bufferSize;
	
	while (buffer.size() > 0){
		delete buffer[0];
		buffer.erase(buffer.begin());
	}
	
	allocate();
}

int	ofxColorsOfMovement::getBufferSize(){
	return buffer.size();
}

void ofxColorsOfMovement::setRIndex(unsigned int index){
	if(index >= getBufferSize() - 1) index = getBufferSize() - 1;
	rIndex = index;
}
void ofxColorsOfMovement::setGIndex(unsigned int index){
	if(index >= getBufferSize() - 1) index = getBufferSize() - 1;
	gIndex = index;
}
void ofxColorsOfMovement::setBIndex(unsigned int index){
	if(index >= getBufferSize() - 1) index = getBufferSize() - 1;
	bIndex = index;
}

int ofxColorsOfMovement::getRIndex(){
	return rIndex;
}
int ofxColorsOfMovement::getGIndex(){
	return gIndex;
}
int	ofxColorsOfMovement::getBIndex(){
	return bIndex;
}

void ofxColorsOfMovement::allocate(){
	beginNormalized();
	
	for (int i = 0; i < bufferSize; i++) {
		ofFbo * frame = new ofFbo();
		frame->allocate(texureSize.x, texureSize.y);
		buffer.push_back(frame);
	}
	
	endNormalized();
}

void ofxColorsOfMovement::beginNormalized(){
	if(ofGetUsingArbTex()) ofDisableArbTex();
	if(!ofGetUsingNormalizedTexCoords()) ofEnableNormalizedTexCoords();
}

void ofxColorsOfMovement::endNormalized(){
	if(ofGetUsingArbTex()) ofEnableArbTex();
	if(!ofGetUsingNormalizedTexCoords()) ofDisableNormalizedTexCoords();
}