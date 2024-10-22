#ifndef THREE_D_PROJECTILE_H
#define THREE_D_PROJECTILE_H

#include "vec3f.h"
#include "3d_wave.h"
#include "functions.h"
#include "sphere.h"
#include "vec3fSpherical.h"

#include <cmath>

#include "opengl.h"

class Projectile3D
{
public:
    Projectile3D(vec3f location, vec3fSpherical sphr, bool isBoat, int segments);
    ~Projectile3D();

    void draw(Wave3D *wave, bool showNormals);
    void drawDot(float x, float y, float z, bool showNormals);

    void updateProjectileState(float dt);

    vec3f getLocation();
    float getRadius();

    bool getCollision(float radius, vec2f location);
    bool getIsBoat();

private:
    vec3f location;
    vec3fSpherical spherical;
    bool isBoat;

    Sphere *sphere;

    vec3f r0 = {0.0, 0.0, 0.0}; // Initial position
    vec3f v0 = {0.0, 0.0, 0.0}; // Initial velocity
    vec3f r = {0.0, 0.0, 0.0};  // Drawn position
    vec3f v = {0.0, 0.0, 0.0};  // Drawn velocity

    float g = -0.25;

    float radius = 0.01;
};

#endif // THREE_D_PROJECTILE_H