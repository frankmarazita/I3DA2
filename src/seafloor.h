#ifndef SEAFLOOR_H
#define SEAFLOOR_H

#include "vec2f.h"
#include "vec3f.h"
#include "colour.h"
#include "functions.h"

#include <cmath>
#include <list>
#include <iostream>

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