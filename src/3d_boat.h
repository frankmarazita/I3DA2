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
#include "cylinder.h"
#include "3d_projectile.h"
#include "vec3fSpherical.h"

#include <cmath>
#include <list>

#include "opengl.h"

class Boat3D
{
public:
    Boat3D(vec3f location, float boatDeg, float boatRotation, float cannonDeg, int segments);

    Projectile3D *shoot();
    void draw(bool showNormals);

    vec3f getLocation();
    vec3f getPrevLocation();
    void setLocation(vec3f location);
    void setPrevLocation();
    void setBoatRotation(float boatRotation);
    void updateBoatRotation();
    void setBoatDeg(float boatDeg);
    float getInitialCannonDeg();
    float getCannonDeg();
    void setCannonDeg(float cannonDeg);
    float getHitboxRadius();
    void calcBoatDegFromPrev();
    void calcProjectileOrigin();
    vec3f getProjectileOrigin();
    bool collision(vec3f otherLocation, float otherRadius);
    void calcProjectilePower();
    int time = 0;

private:
    vec3f location;
    vec3f prevLocation;
    float boatDeg;
    float boatRotation;
    vec3f projectileOrigin;
    vec2fPolar projectilePolar = {0.5, 90};
    float initialCannonDeg;

    float hitboxRadius = 1.1;
    float scale = 0.1;
    int health = 1;

    const float cooldownTime = 2500;
    float shootTime = -1;

    colour col = {1, 0, 0, 1};

    vec3fSpherical sphericalVec = {0.4, 45, 0.0};

    int segments;
};

#endif // THREE_D_BOAT_H
