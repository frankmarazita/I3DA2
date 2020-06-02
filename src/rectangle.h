#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "vec2f.h"
#include "vec2fPolar.h"
#include "vec3f.h"
#include "functions.h"
#include "3d_wave.h"

#include <cmath>
#include <list>

#include "opengl.h"
#include "texture.h"

class Rectangle3D
{
public:
    Rectangle3D(float length, float width, float depth);
    void draw();


private:
    float length, width, depth;
};

#endif // RECTANGLE_H