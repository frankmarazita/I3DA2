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
#include "half_cylinder.h"
#include "rectangle.h"
#include "3d_projectile.h"
#include "vec3fSpherical.h"
#include "sphere.h"
#include "3d_defence.h"

// Rotation speeds for the cannon
#define CANNON_ROTATION_SPEED 2.0
#define CANNON_TILT_SPEED 1.0

#define CANNON_DEFAULT_POWER 0.4
#define CANNON_POWER_INCREASE_FACTOR 0.02
#define CANNON_POWER_DECREASE_FACTOR 0.02

#define ISLAND_BASE_RADIUS 0.25

// The offsets applied on top of the angles so the position of 0 degrees is moved
#define CANNON_PITCH_OFFSET -90.0
#define CANNON_ROTATION_OFFSET 0.0

// Limits applied to the cannons tilt and rotation
#define CANNON_TILT_MAX 90.0
#define CANNON_TILT_MIN -10.0

// Cannon cylinder, the actual gun
#define CANNON_RADIUS 0.02
#define CANNON_LENGTH 0.19

// Island/cannon base holder cylinder
// the one that pokes out from the island and the gun base sits on
// not the half cylinder

#define CANNON_BASE_CYLINDER_RADIUS 0.10
#define CANNON_BASE_CYLINDER_HEIGHT 0.20
#define CANNON_BASE_CYLINDER_OFFSET_FROM_SPHERE 0.06 // The offset from the central position of the sphere on the y axis

// Dimensions of the cannon gun bases half cylinder
#define CANNON_BASE_HALF_CYLINDER_SIZE 0.11
#define CANNON_BASE_HALF_CYLINDER_RADIUS 0.06

// Height of the square box holding the half cylinder
#define GUN_BOX_HEIGHT 0.04

// Offset of the base from the island cylinder holding it
// 1 - 0.51 - 0.25 - 0.04/2.0
#define CANNON_BASE_OFFSET 0.22

class Island3D
{
public:
    Island3D();
    void draw();
    void drawHealth();
    void drawScore();

    bool collision(vec3f otherLocation, float otherRadius);
    void damage();

    Cylinder *bottomCylinder;
    Cylinder *cannon;
    Cylinder *cannonBaseMiddle;
    HalfCylinder *cannonGunBaseCylinder;
    Rectangle3D *gunBox;

    Sphere *sphere = new Sphere(ISLAND_BASE_RADIUS, 40, 40);

    //vec2fPolar cannonYaw = { 0.4, 90 };
    //vec2fPolar cannonPitch = { 0.4, 90 };

    vec3fSpherical cannonSph = {CANNON_DEFAULT_POWER, 0.0, 0.0}; // magnitude, azimuthal, polar

    /*float cannonRotation = 90.0;
    float cannonPitch = 90.0;*/

    void tiltCannonUp();
    void tiltCannonDown();

    void rotateCannonLeft();
    void rotateCannonRight();

    void increaseCannonPower();
    void decreaseCannonPower();

    vec3f endOfCannon();

    Projectile3D *shoot();
    Defence3D *defence();

    void point();

    bool getAlive();

    //Projectile3D* shoot();
    Texture *texture;

private:
    GLUquadric *qobj;

    vec3f location = {0, -0.5, 0};
    vec3f cannonLocation = {0, 0, 0};
    vec2fPolar ProjectilePolar = {0.4, 45};

    int health = 100;
    int score = 0;

    const float cooldownTime = 1000;
    float shootTime = -1;
    float defenceTime = -1;

    colour col = {0.9, 0.8, 0.5, 1.0};
};

#endif // THREE_D_ISLAND_H