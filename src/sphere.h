#ifndef SPHERE_H
#define SPHERE_H

#ifndef M_PI
#define M_PI 3.141592653589793238463
#endif

#include "vec3f.h"
#include "tex2f.h"

#include <cmath>

#include "opengl.h"

#define SPHERE_STACKS_MAX 64
#define SPHERE_SLICES_MAX 64

class Sphere
{
public:
    Sphere(float r, int stacks, int slices);
    ~Sphere();

    void draw(bool showNormals);

private:
    int stacks;
    int slices;
    float r;

    vec3f** vertices;
    tex2f** texes;
};

#endif // SPHERE_H
