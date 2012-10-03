/**
* ColorsOfMovement
* Author: Paulo Barcelos
* https://github.com/paulobarcelos/ColorsOfMovement
**/

#pragma once

#include "ofMain.h"

class ColorsOfMovement {
public:
	ColorsOfMovement();
	
	void setup(int width, int height, unsigned int bufferSize = 30);
	void addFrame(ofBaseDraws * frame);
	
	void draw();
	
	void setBufferSize(unsigned int size);
	int	getBufferSize();
	
	void setRIndex(unsigned int index);
	void setGIndex(unsigned int index);
	void setBIndex(unsigned int index);
	
	int getRIndex();
	int getGIndex();
	int	getBIndex();
	
private:	
	int	width, height;
	
	vector <ofFbo *> buffer;
	
	int index;
	int rIndex;
	int gIndex;
	int bIndex;
};