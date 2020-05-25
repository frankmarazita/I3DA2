#ifndef THREE_D_WAVE_H
#define THREE_D_WAVE_H

#include "vec2f.h"
#include "vec3f.h"
#include "colour.h"
#include "functions.h"

#include <cmath>
#include <list>
#include <iostream>

#include "opengl.h"

class Wave3D
{
public:
	Wave3D(float windowSize, float numSegments, float a, float b, float c, float d);

	void draw();
	void drawTom();
	void drawTom2();

	void moveWave(float amount);
	void calcVerticies();

	float getYfromX(float x);
	float getGrad(float x);
	bool getAnimate();
	int getNumSegments();

	void toggleNormal();
	void toggleTangent();
	void toggleAnimation();
	void increaseNumSegments();
	void decreaseNumSegments();
	void drawVector(vec3f point, float m, float s, bool normalize);

private:
	void setLighting();
	void disableLighting();
	float windowSize;
	int numSegments;
	float getGradientForSine(float x);
	float segmentSize;

	float a;
	float b;
	float c;
	float d;

	bool normal = false;
	bool tangent = false;
	bool animate = true;
	bool wireframe = false;

	colour col = { 0.2, 0.5, 1.0, 0.75 };

	std::list<vec2f>
		verticies;
};

#endif // WAVE_H