/**
* ColorsOfMovement
* Author: Paulo Barcelos
* https://github.com/paulobarcelos/ColorsOfMovement
**/

#pragma once

#include "ofMain.h"

#define STRINGIFY(A) #A

static string OFXCM_VERTEX_SHADER = STRINGIFY(
											  void main(void){
												  gl_TexCoord[0] = gl_MultiTexCoord0;
												  gl_Position = ftransform();
												  gl_FrontColor = gl_Color;
											  }
											  );

static string OFXCM_FRAGMENT_SHADER = STRINGIFY(
												uniform sampler2D texR;
												uniform sampler2D texG;
												uniform sampler2D texB;
												
												uniform float gamma;
												
												uniform float brightness;
												uniform float saturation;
												uniform float contrast;
												uniform float hueShift;
												
												uniform mat3 tone;
												
												vec3 setTone(vec3 color, mat3 matrix){
													return color * matrix;
												}
												
												vec3 setGamma(vec3 color, float gamma){
													return vec3(pow(color.r, gamma), pow(color.g, gamma), pow(color.b, gamma));
												}
												
												vec3 setBrightnessSaturationContrast(vec3 color, float brightness, float saturation, float contrast){
													const float AvgLumR = 0.5;
													const float AvgLumG = 0.5;
													const float AvgLumB = 0.5;
													
													const vec3 LumCoeff = vec3(0.2125, 0.7154, 0.0721);
													
													vec3 AvgLumin = vec3(AvgLumR, AvgLumG, AvgLumB);
													vec3 brtColor = color * brightness;
													vec3 intensity = vec3(dot(brtColor, LumCoeff));
													vec3 satColor = mix(intensity, brtColor, saturation);
													vec3 conColor = mix(AvgLumin, satColor, contrast);
													
													return conColor;
												}
												
												vec3 setHueShift(vec3 color, float shift){
													shift *= 6.28318531; //normalize to two pi
													
													const vec3  kRGBToYPrime = vec3 (0.299, 0.587, 0.114);
													const vec3  kRGBToI     = vec3 (0.596, -0.275, -0.321);
													const vec3  kRGBToQ     = vec3 (0.212, -0.523, 0.311);
													
													const vec3  kYIQToR   = vec3 (1.0, 0.956, 0.621);
													const vec3  kYIQToG   = vec3 (1.0, -0.272, -0.647);
													const vec3  kYIQToB   = vec3 (1.0, -1.107, 1.704);
													
													// Convert to YIQ
													float   YPrime  = dot (color, kRGBToYPrime);
													float   I      = dot (color, kRGBToI);
													float   Q      = dot (color, kRGBToQ);
													
													// Calculate the hue and chroma
													float   hue     = atan (Q, I);
													float   chroma  = sqrt (I * I + Q * Q);
													
													// Make the user's adjustments
													hue += shift;
													
													// Convert back to YIQ
													Q = chroma * sin (hue);
													I = chroma * cos (hue);
													
													// Convert back to RGB
													vec3 yIQ   = vec3 (YPrime, I, Q);
													color.r = dot (yIQ, kYIQToR);
													color.g = dot (yIQ, kYIQToG);
													color.b = dot (yIQ, kYIQToB);
													
													return color;
												}
												
												void main(void){
													vec3 r = texture2D(texR, gl_TexCoord[0].st).rgb;
													vec3 g = texture2D(texG, gl_TexCoord[0].st).rgb;
													vec3 b = texture2D(texB, gl_TexCoord[0].st).rgb;
													
													r = setGamma(r, gamma);
													r = setBrightnessSaturationContrast(r, brightness, saturation, contrast);
													r = setTone(r, tone);
													r = setHueShift(r, hueShift);
													
													g = setGamma(g, gamma);
													g = setBrightnessSaturationContrast(g, brightness, saturation, contrast);
													g = setTone(g, tone);
													g = setHueShift(g, hueShift);
													
													b = setGamma(b, gamma);
													b = setBrightnessSaturationContrast(b, brightness, saturation, contrast);
													b = setTone(b, tone);
													b = setHueShift(b, hueShift);
													
													vec4 color = vec4(r.r, g.g, b.b, 1.0);
													
													gl_FragColor = color;
													
												}
												);

class ofxColorsOfMovement : public ofBaseHasTexture {
public:
	ofxColorsOfMovement();
	
	void setup(ofVec2f texSize, unsigned int bufferSize);
	void addFrame(ofBaseDraws * frame);
	
	ofTexture & getTextureReference();
	void setUseTexture(bool bUseTex){};
	
	void setTextureSize(ofVec2f texureSize, bool reallocate = true);
	ofVec2f getTextureSize();
	
	void setBufferSize(unsigned int bufferSize);
	int	getBufferSize();
	
	void setRPosition(float postion);
	float getRPosition();
	
	void setGPosition(float postion);
	float getGPosition();
	
	void setBPosition(float postion);
	float getBPosition();
	
	void setGamma(float value);
	float getGamma();
	
	void setBrightness(float value);
	float getBrightness();
	
	void setSaturation(float value);
	float getSaturation();
	
	void setContrast(float value);
	float getContrast();
	
	void setHueShift(float value);
	float getHueShift();
	
private:
	bool isSetup;
	ofShader shader;
	ofVboMesh vbo;
	ofFbo fbo;
	vector <ofFbo *> buffer;	
	
	ofVec2f texureSize;
	unsigned int bufferSize;
	
	float rPosition;
	float gPosition;
	float bPosition;
	float gamma;
	float brightness;
	float saturation;
	float contrast;
	float hueShift;
	float* tone;
	
	int index;	
	int internalRIndex;
	int internalGIndex;
	int internalBIndex;
	
	void allocate();
	
	void beginNormalized();
	void endNormalized();
};