#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cmath>

#include "opengl.h"

class Rectangle3D
{
public:
    Rectangle3D(float length, float width, float depth);
    void draw();


private:
    float length, width, depth;
};

#endif // RECTANGLE_H