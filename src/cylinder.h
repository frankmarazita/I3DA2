#ifndef CYLINDER_H
#define CYLINDER_H

#include "vec2f.h"
#include "vec2fPolar.h"
#include "vec3f.h"
#include "functions.h"
#include "3d_wave.h"

#include <cmath>
#include <list>

#include "opengl.h"
#include "texture.h"

class Cylinder
{
public:
	Cylinder(float radius, float height, float segments);
	void draw();


private:
	Texture* texture;
	float segments;
	float radius;
	float height;
};

#endif // CYLINDER_H