#include "ofxColorsOfMovement.h"

ofxColorsOfMovement::ofxColorsOfMovement():
index(-1),
rPosition(0),
gPosition(0),
bPosition(0),
pre_gamma(1.0),
pre_brightness(1.0),
pre_saturation(1.0),
pre_contrast(1.0),
pre_tone(new float[9]),
post_gamma(1.0),
post_brightness(1.0),
post_saturation(1.0),
post_contrast(1.0),
post_tone(new float[9]),
isSetup(false)
{
	vbo.setMode(OF_PRIMITIVE_TRIANGLES);
	
	shader.setupShaderFromSource(GL_VERTEX_SHADER, OFXCM_VERTEX_SHADER);
	shader.setupShaderFromSource(GL_FRAGMENT_SHADER, OFXCM_FRAGMENT_SHADER);
	shader.linkProgram();
	
	pre_tone[0] = 1.0;
	pre_tone[1] = 0.0;
	pre_tone[2] = 0.0;
	
	pre_tone[3] = 0.0;
	pre_tone[4] = 1.0;
	pre_tone[5] = 0.0;

	pre_tone[6] = 0.0;
	pre_tone[7] = 0.0;
	pre_tone[8] = 1.0;
	
	post_tone[0] = 1.0;
	post_tone[1] = 0.0;
	post_tone[2] = 0.0;
	
	post_tone[3] = 0.0;
	post_tone[4] = 1.0;
	post_tone[5] = 0.0;
	
	post_tone[6] = 0.0;
	post_tone[7] = 0.0;
	post_tone[8] = 1.0;
}

void ofxColorsOfMovement::setup(ofVec2f texureSize, unsigned int bufferSize){
	isSetup = true;
	
	setTextureSize(texureSize, false);
	setBufferSize(bufferSize);
	
	#ifndef OFXCM_DISABLE_DEFAULT_GUI
	gui.setup("Colors of Movement", "ColorsOfMovement.xml");
	ofxLabel * mixLabel = new ofxLabel();
	mixLabel->setup("Channel Mixer", "Channel Mixer", 200, 40);
	gui.add(mixLabel);
	
    
    
	//ofxIntSlider * buffer = new ofxIntSlider("Buffer Size", 30, 1, 300);
	ofxIntSlider * buffer = new ofxIntSlider();
    buffer->setup("Buffer Size", 30, 1, 300);
    
    buffer->addListener(this, &ofxColorsOfMovement::onGuiIntChange);
	gui.add(buffer);
	
	//ofxFloatSlider * red = new ofxFloatSlider("Red Position", 0, 0, 1);
	ofxFloatSlider * red = new ofxFloatSlider();
    red->setup("Red Position", 0, 0, 1);
    red->addListener(this, &ofxColorsOfMovement::onGuiFloatChange);
	gui.add(red);
	
	//ofxFloatSlider * green = new ofxFloatSlider("Green Position", 0, 0, 1);
	ofxFloatSlider * green = new ofxFloatSlider();
    green->setup("Green Position", 0, 0, 1);
    green->addListener(this, &ofxColorsOfMovement::onGuiFloatChange);
	gui.add(green);
	
	//ofxFloatSlider * blue = new ofxFloatSlider("Blue Position", 0, 0, 1);
	ofxFloatSlider * blue = new ofxFloatSlider();
    blue->setup("Blue Position", 0, 0, 1);
    
    blue->addListener(this, &ofxColorsOfMovement::onGuiFloatChange);
	gui.add(blue);
	
	
	ofxLabel * preLabel = new ofxLabel();
	preLabel->setup("Pre Effects", "Pre Effects", 200, 40);
	gui.add(preLabel);
	
	ofxFloatSlider * pre_gamma = new ofxFloatSlider();
    pre_gamma->setup("Pre Gamma", 1, 0, 5);
	pre_gamma->addListener(this, &ofxColorsOfMovement::onGuiFloatChange);
	gui.add(pre_gamma);
	
	ofxFloatSlider * pre_brightness = new ofxFloatSlider();
    pre_brightness->setup("Pre Brightness", 1, 0, 5);
	pre_brightness->addListener(this, &ofxColorsOfMovement::onGuiFloatChange);
	gui.add(pre_brightness);
	
	ofxFloatSlider * pre_saturation = new ofxFloatSlider();
    pre_saturation->setup("Pre Saturation", 1, 0, 5);
	pre_saturation->addListener(this, &ofxColorsOfMovement::onGuiFloatChange);
	gui.add(pre_saturation);
	
	ofxFloatSlider * pre_contrast = new ofxFloatSlider();
    pre_contrast->setup("Pre Contrast", 1, 0, 5);
	pre_contrast->addListener(this, &ofxColorsOfMovement::onGuiFloatChange);
	gui.add(pre_contrast);
	
	ofxFloatSlider * pre_hueShift = new ofxFloatSlider();
    pre_hueShift->setup("Pre Hue Shift", 0, -1, 1);
	pre_hueShift->addListener(this, &ofxColorsOfMovement::onGuiFloatChange);
	gui.add(pre_hueShift);
	
	
	
	ofxLabel * postLabel = new ofxLabel();
	postLabel->setup("Post Effects", "Post Effects", 200, 40);
	gui.add(postLabel);
	
	ofxFloatSlider * post_gamma = new ofxFloatSlider();
    post_gamma->setup("Post Gamma", 1, 0, 5);
	post_gamma->addListener(this, &ofxColorsOfMovement::onGuiFloatChange);
	gui.add(post_gamma);
	
	ofxFloatSlider * post_brightness = new ofxFloatSlider();
    post_brightness->setup("Post Brightness", 1, 0, 5);
	post_brightness->addListener(this, &ofxColorsOfMovement::onGuiFloatChange);
	gui.add(post_brightness);
	
	ofxFloatSlider * post_saturation = new ofxFloatSlider();
    post_saturation->setup("Post Saturation", 1, 0, 5);
	post_saturation->addListener(this, &ofxColorsOfMovement::onGuiFloatChange);
	gui.add(post_saturation);
	
	ofxFloatSlider * post_contrast = new ofxFloatSlider();
    post_contrast->setup("Post Contrast", 1, 0, 5);
	post_contrast->addListener(this, &ofxColorsOfMovement::onGuiFloatChange);
	gui.add(post_contrast);
	
	ofxFloatSlider * post_hueShift = new ofxFloatSlider();
    post_hueShift->setup("Post Hue Shift", 0, -1, 1);
	post_hueShift->addListener(this, &ofxColorsOfMovement::onGuiFloatChange);
	gui.add(post_hueShift);
	
	gui.loadFromFile("ColorsOfMovement.xml");
	#endif
}
void ofxColorsOfMovement::addFrame(ofBaseDraws * frame){
	if(!isSetup || !buffer.size()) return;
	
	ofPushStyle();
	ofSetColor(255);
	
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
	
	fbo.begin();
	beginGLSettings();
	shader.begin();	
	shader.setUniformTexture("texR", buffer[internalRIndex]->getTexture(), 0 );
	shader.setUniformTexture("texG", buffer[internalGIndex]->getTexture(), 1 );
	shader.setUniformTexture("texB", buffer[internalBIndex]->getTexture(), 2 );
	shader.setUniform1f("pre_gamma", pre_gamma );
	shader.setUniform1f("pre_brightness", pre_brightness );
	shader.setUniform1f("pre_saturation", pre_saturation );
	shader.setUniform1f("pre_contrast", pre_contrast );
	shader.setUniform1f("pre_hueShift", pre_hueShift );
	glUniformMatrix3fv(glGetUniformLocation(shader.getProgram(), "pre_tone"), 1, GL_FALSE, pre_tone);
	shader.setUniform1f("post_gamma", post_gamma );
	shader.setUniform1f("post_brightness", post_brightness );
	shader.setUniform1f("post_saturation", post_saturation );
	shader.setUniform1f("post_contrast", post_contrast );
	shader.setUniform1f("post_hueShift", post_hueShift );
	glUniformMatrix3fv(glGetUniformLocation(shader.getProgram(), "post_tone"), 1, GL_FALSE, post_tone);
	vbo.draw();
	shader.end();
	endGLSettings();
	fbo.end();
	
	ofPopStyle();
}

ofTexture & ofxColorsOfMovement::getTextureReference(){
	return fbo.getTexture();
}

void ofxColorsOfMovement::setTextureSize(ofVec2f texureSize, bool reallocate){
	if(this->texureSize == texureSize) return;
	this->texureSize = texureSize;
	
	float coordWidth = texureSize.x;//(float)texureSize.x / ofNextPow2(texureSize.x);
	float coordHeight = texureSize.y;//(float)texureSize.y / ofNextPow2(texureSize.y);
	
	vbo.clearTexCoords();
	vbo.addTexCoord(ofVec2f(0,0));
	vbo.addTexCoord(ofVec2f(coordWidth,0));
	vbo.addTexCoord(ofVec2f(0,coordHeight));
	
	vbo.addTexCoord(ofVec2f(0,coordHeight));
	vbo.addTexCoord(ofVec2f(coordWidth,0));
	vbo.addTexCoord(ofVec2f(coordWidth,coordHeight));
	
	vbo.clearVertices();
	vbo.addVertex(ofPoint(0,0,0));
	vbo.addVertex(ofPoint(texureSize.x,0,0));
	vbo.addVertex(ofPoint(0,texureSize.y,0));
	
	vbo.addVertex(ofPoint(0,texureSize.y,0));
	vbo.addVertex(ofPoint(texureSize.x,0,0));
	vbo.addVertex(ofPoint(texureSize.x,texureSize.y,0));
	
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

void ofxColorsOfMovement::setPreGamma(float value){
	pre_gamma = value;
}
float ofxColorsOfMovement::getPreGamma(){
	return pre_gamma;
}

void ofxColorsOfMovement::setPreBrightness(float value){
	pre_brightness = value;
}
float ofxColorsOfMovement::getPreBrightness(){
	return pre_brightness;
}

void ofxColorsOfMovement::setPreSaturation(float value){
	pre_saturation = value;
}
float ofxColorsOfMovement::getPreSaturation(){
	return pre_saturation;
}

void ofxColorsOfMovement::setPreContrast(float value){
	pre_contrast = value;
}
float ofxColorsOfMovement::getPreContrast(){
	return pre_contrast;
}

void ofxColorsOfMovement::setPreHueShift(float value){
	pre_hueShift = value;
}
float ofxColorsOfMovement::getPreHueShift(){
	return pre_hueShift;
}

void ofxColorsOfMovement::setPostGamma(float value){
	post_gamma = value;
}
float ofxColorsOfMovement::getPostGamma(){
	return post_gamma;
}

void ofxColorsOfMovement::setPostBrightness(float value){
	post_brightness = value;
}
float ofxColorsOfMovement::getPostBrightness(){
	return post_brightness;
}

void ofxColorsOfMovement::setPostSaturation(float value){
	post_saturation = value;
}
float ofxColorsOfMovement::getPostSaturation(){
	return post_saturation;
}

void ofxColorsOfMovement::setPostContrast(float value){
	post_contrast = value;
}
float ofxColorsOfMovement::getPostContrast(){
	return post_contrast;
}

void ofxColorsOfMovement::setPostHueShift(float value){
	post_hueShift = value;
}
float ofxColorsOfMovement::getPostHueShift(){
	return post_hueShift;
}

void ofxColorsOfMovement::allocate(){
	beginGLSettings();
	
	fbo.allocate(texureSize.x, texureSize.y);
	
	for (int i = 0; i < bufferSize; i++) {
		ofFbo * frame = new ofFbo();
		frame->allocate(texureSize.x, texureSize.y);
		buffer.push_back(frame);
	}
	
	endGLSettings();
}

void ofxColorsOfMovement::beginGLSettings(){
	wasUsingARB = ofGetUsingArbTex();
	wasUsingNormalizedCoords = ofGetUsingNormalizedTexCoords();
	if(!wasUsingARB) ofEnableArbTex();
	if(wasUsingNormalizedCoords) ofDisableNormalizedTexCoords();
}
void ofxColorsOfMovement::endGLSettings(){
	if(!wasUsingARB) ofEnableArbTex();
	if(wasUsingNormalizedCoords) ofEnableNormalizedTexCoords();
}

#ifndef OFXCM_DISABLE_DEFAULT_GUI
void ofxColorsOfMovement::drawGui(){
	gui.draw();
	
}
void ofxColorsOfMovement::onGuiIntChange(int & value){
	setBufferSize(gui.getIntSlider("Buffer Size"));
}

void ofxColorsOfMovement::onGuiFloatChange(float & value){
	setRPosition(gui.getFloatSlider("Red Position"));
	setGPosition(gui.getFloatSlider("Green Position"));
	setBPosition(gui.getFloatSlider("Blue Position"));
	
	setPreGamma(gui.getFloatSlider("Pre Gamma"));
	setPreBrightness(gui.getFloatSlider("Pre Brightness"));
	setPreSaturation(gui.getFloatSlider("Pre Saturation"));
	setPreContrast(gui.getFloatSlider("Pre Contrast"));
	setPreHueShift(gui.getFloatSlider("Pre Hue Shift"));
	
	setPostGamma(gui.getFloatSlider("Post Gamma"));
	setPostBrightness(gui.getFloatSlider("Post Brightness"));
	setPostSaturation(gui.getFloatSlider("Post Saturation"));
	setPostContrast(gui.getFloatSlider("Post Contrast"));
	setPostHueShift(gui.getFloatSlider("Post Hue Shift"));
}
#endif