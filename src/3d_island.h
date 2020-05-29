#ifndef THREE_D_ISLAND_H
#define THREE_D_ISLAND_H

#include "vec2f.h"
#include "vec2fPolar.h"
#include "vec3f.h"
#include "functions.h"
#include "3d_wave.h"
#include "cylinder.h"

#include <cmath>
#include <list>
#include <string>

#include "opengl.h"
#include "texture.h"

#define CANNON_ROTATION_SPEED 2.0
#define CANNON_TILT_SPEED 1.0

#define CANNON_TILT_MAX 180.0
#define CANNON_TILT_MIN 0.0

class Island3D
{
public:
    Island3D();
    void draw();
    void drawHealth();
    void drawScore();

    bool collision(vec3f otherLocation, float otherRadius);
    void damage();

    Cylinder *cannon;
    Cylinder *cannonBaseMiddle;
    Cylinder *cannonGunBaseCylinder;

    float cannonRotation = 90.0;
    float cannonPitch = 90.0;

    void tiltCannonUp();
    void tiltCannonDown();

private:
    Texture *texture;
    GLUquadric *qobj;

    vec3f location = {0, -0.5, 0};
    vec3f cannonLocation = {0, 0, 0};
    vec2fPolar ProjectilePolar = {0.4, 45};

    int health = 100;
    int score = 0;
    float radius = 0.25;

    const float cooldownTime = 1000;
    float shootTime = -1;

    colour col = {0.9, 0.8, 0.5, 1.0};
};

#endif // THREE_D_ISLAND_H