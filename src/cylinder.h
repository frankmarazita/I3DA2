#ifndef CYLINDER_H
#define CYLINDER_H

#ifndef M_PI
#define M_PI 3.141592653589793238463
#endif

#include "vec3f.h"

#include <cmath>
#include <list>

#include "opengl.h"
#include "texture.h"

class Cylinder
{
public:
	Cylinder(float radius, float height, float segments);
	void draw(bool showNormals);


private:
	float segments;
	float radius;
	float height;
};

#endif // CYLINDER_H