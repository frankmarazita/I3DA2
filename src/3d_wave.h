#ifndef THREE_D_WAVE_H
#define THREE_D_WAVE_H

#include "vec2f.h"
#include "vec3f.h"
#include "colour.h"
#include "functions.h"

#include <cmath>
#include <vector>
#include <iostream>

#include "opengl.h"

class Wave3D
{
public:
	Wave3D(float windowSize, float numSegments, float a, float b, float k, float c, float d);

	void drawAdvanced();

	void moveWave(float amount);
	void calcVerticies();
	void update();

	float getYfromXZ(float x, float z);
	vec3f getGradientForAdvancedSine(float x, float z);
	bool getAnimate();
	int getNumSegments();

	void toggleNormal();
	void toggleTangent();
	void toggleAnimation();
	void increaseNumSegments();
	void decreaseNumSegments();
	void drawVector(vec3f point, vec3f m, float s, bool normalize);

private:
	float windowSize;
	int numSegments;
	float segmentSize;

	void setLighting();
	void disableLighting();

	float a, b, c, d, k;

	bool normal = false;
	bool tangent = false;
	bool animate = true;
	bool wireframe = false;

	colour col = {0.2, 0.5, 1.0, 0.75};

	std::vector<vec3f> verticies;
};

#endif // THREE_D_WAVE_H