#ifndef THREE_D_BOAT_H
#define THREE_D_BOAT_H

#include "vec2f.h"
#include "vec2fPolar.h"
#include "vec3f.h"
#include "colour.h"
#include "functions.h"
#include "projectile.h"
#include "defence.h"
#include "wave.h"

#include <cmath>
#include <list>

#include "opengl.h"

class Boat3D
{
public:
    Boat3D(vec3f location, float boatDeg, float cannonDeg);

    void draw();

private:
    vec3f location;
    float boatDeg;
    vec2fPolar projectilePolar = {0.5, 90};

    colour col = {1, 0, 0, 1};
};

#endif // THREE_D_BOAT_H
