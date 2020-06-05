#ifndef HALF_CYLINDER_H
#define HALF_CYLINDER_H

#ifndef M_PI
#define M_PI 3.141592653589793238463
#endif

#include <cmath>

#include "opengl.h"

class HalfCylinder
{
public:
    HalfCylinder(float radius, float height, float segments);
    void draw(bool showNormals);


private:
    float segments;
    float radius;
    float height;
};

#endif // HALF_CYLINDER_H