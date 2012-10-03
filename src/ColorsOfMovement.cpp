#include "ColorsOfMovement.h"

ColorsOfMovement::ColorsOfMovement():
rIndex(0),
gIndex(0),
bIndex(0),
width(0),
height(0)
{}

void ColorsOfMovement::setup(int width, int height, unsigned int bufferSize){	
	this->width = width;
	this->height = height;
	
	setBufferSize(bufferSize);
}

void ColorsOfMovement::addFrame(ofBaseDraws * frame){
	if(!buffer.size()) return;
	
	buffer[index]->begin();
	frame->draw(0, 0, width, height);
	buffer[index]->end();
}

void ColorsOfMovement::draw(){
	if(!buffer.size()) return;
	
	buffer[rIndex]->draw(0, 0, 100, 100);
	buffer[gIndex]->draw(100, 0, 100, 100);
	buffer[bIndex]->draw(200, 0, 100, 100);
}


void ColorsOfMovement::setBufferSize(unsigned int size){
	index = 0;
	
	while (buffer.size() > 0){
		delete buffer[0];
		buffer.erase(buffer.begin());
	}
	
	for (int i = 0; i < size; i++) {
		ofFbo * frame = new ofFbo();
		frame->allocate(width, height);
		buffer.push_back(frame);
	}
}

int	ColorsOfMovement::getBufferSize(){
	return buffer.size();
}

void ColorsOfMovement::setRIndex(unsigned int index){
	if(index >= getBufferSize() - 1) index = getBufferSize() - 1;
	rIndex = index;
}
void ColorsOfMovement::setGIndex(unsigned int index){
	if(index >= getBufferSize() - 1) index = getBufferSize() - 1;
	rIndex = index;
}
void ColorsOfMovement::setBIndex(unsigned int index){
	if(index >= getBufferSize() - 1) index = getBufferSize() - 1;
	rIndex = index;
}

int ColorsOfMovement::getRIndex(){
	return rIndex;
}
int ColorsOfMovement::getGIndex(){
	return gIndex;
}
int	ColorsOfMovement::getBIndex(){
	return bIndex;
}