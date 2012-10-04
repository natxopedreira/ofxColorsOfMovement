#include "ofxColorsOfMovement.h"

ofxColorsOfMovement::ofxColorsOfMovement():
index(-1),
rPosition(0),
gPosition(0),
bPosition(0),
gamma(1.0),
brightness(1.0),
saturation(1.0),
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
	
	float last = (float)(buffer.size()-1);
	internalRIndex = index - int(rPosition * last);
	internalGIndex = index - int(gPosition * last);
	internalBIndex = index - int(bPosition * last);
	
	if(internalRIndex < 0) internalRIndex += buffer.size();
	if(internalGIndex < 0) internalGIndex += buffer.size();
	if(internalBIndex < 0) internalBIndex += buffer.size();
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
	shader.setUniform1f("saturation", saturation );
	shader.setUniform1f("contrast", contrast );
	shader.setUniform1f("hueShift", hueShift );
	// there is no built in "setUniform" for mat3x3 in ofShader
	glUniformMatrix3fv(glGetUniformLocation(shader.getProgram(), "tone"), 1, GL_FALSE, tone);

	vbo.draw();
	
	shader.end();
	
	endNormalized();	
}

void ofxColorsOfMovement::setRectangle(ofRectangle rectangle){
	if(this->rectangle == rectangle) return;
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
	if(this->texureSize == texureSize) return;
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
	if(this->bufferSize == bufferSize) return;
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

void ofxColorsOfMovement::setRPosition(float position){
	position = ofClamp(position, 0, 1);
	rPosition = position;
}
float ofxColorsOfMovement::getRPosition(){
	return rPosition;
}

void ofxColorsOfMovement::setGPosition(float position){
	position = ofClamp(position, 0, 1);
	gPosition = position;
}
float ofxColorsOfMovement::getGPosition(){
	return gPosition;
}

void ofxColorsOfMovement::setBPosition(float position){
	position = ofClamp(position, 0, 1);
	bPosition = position;
}
float	ofxColorsOfMovement::getBPosition(){
	return bPosition;
}

void ofxColorsOfMovement::setGamma(float value){
	gamma = value;
}
float ofxColorsOfMovement::getGamma(){
	return gamma;
}

void ofxColorsOfMovement::setBrightness(float value){
	brightness = value;
}
float ofxColorsOfMovement::getBrightness(){
	return brightness;
}

void ofxColorsOfMovement::setSaturation(float value){
	saturation = value;
}
float ofxColorsOfMovement::getSaturation(){
	return saturation;
}

void ofxColorsOfMovement::setContrast(float value){
	contrast = value;
}
float ofxColorsOfMovement::getContrast(){
	return contrast;
}

void ofxColorsOfMovement::setHueShift(float value){
	hueShift = value;
}
float ofxColorsOfMovement::getHueShift(){
	return hueShift;
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