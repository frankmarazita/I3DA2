#ifndef THREE_D_ISLAND_H
#define THREE_D_ISLAND_H

#include "vec2f.h"
#include "vec2fPolar.h"
#include "vec3f.h"
#include "functions.h"
#include "3d_wave.h"

#include <cmath>
#include <list>

#include "opengl.h"
#include "texture.h"

class Island3D
{
public:
    Island3D();
    void draw();

    bool collision(vec3f location);

private:
    Texture *texture;
    GLUquadric *qobj;

    float radius = 0.25;
};

#endif // THREE_D_ISLAND_H