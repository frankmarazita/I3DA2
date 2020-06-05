#ifndef SEAFLOOR_H
#define SEAFLOOR_H

#include <cmath>

#include "opengl.h"
#include "texture.h"

class Seafloor
{
public:
	Seafloor(float windowSize);

	void draw();

private:
	float windowSize;
	Texture* texture; // Holds the texture for our seafloor, which is setup in the constructor
};

#endif