#ifndef HALF_CYLINDER_H
#define HALF_CYLINDER_H

#include "vec2f.h"
#include "vec2fPolar.h"
#include "vec3f.h"
#include "functions.h"
#include "3d_wave.h"

#include <cmath>
#include <list>

#include "opengl.h"
#include "texture.h"

class HalfCylinder
{
public:
    HalfCylinder(float radius, float height, float segments);
    void draw(bool showNormals);


private:
    Texture* texture;
    float segments;
    float radius;
    float height;
};

#endif // HALF_CYLINDER_H