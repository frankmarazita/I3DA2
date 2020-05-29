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
    Boat3D(vec3f location, float boatDeg, float boatRotation, float cannonDeg);

    void draw();

    vec3f getLocation();
    vec3f getPrevLocation();
    void setLocation(vec3f location);
    void setPrevLocation();
    void setBoatRotation(float boatRotation);
    void updateBoatRotation();
    void setBoatDeg(float boatDeg);
    void calcBoatDegFromPrev();

private:
    vec3f location;
    float boatDeg;
    float boatRotation;
    vec2fPolar projectilePolar = {0.5, 90};

    vec3f prevLocation;

    float scale = 0.1;
    int health = 1;
    bool projectileExists = false;

    colour col = {1, 0, 0, 1};
};

#endif // THREE_D_BOAT_H
