#ifndef SPHERE_H
#define SPHERE_H

#include "vec2f.h"
#include "vec2fPolar.h"
#include "vec3f.h"
#include "colour.h"
#include "functions.h"
#include "projectile.h"
#include "defence.h"
#include "wave.h"
#include "cylinder.h"

#include <cmath>
#include <list>

#include "opengl.h"

class Sphere
{
public:
    Sphere(float r, int stacks, int slices);

    void draw();

private:
    int stacks;
    int slices;
    float r;

    int nv;

    std::list<vec3f> verticies;
};

#endif // SPHERE_H
