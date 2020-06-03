#ifndef THREE_D_DEFENCE_H
#define THREE_D_DEFENCE_H

#include "vec2f.h"
#include "vec2fPolar.h"
#include "vec3f.h"
#include "colour.h"
#include "functions.h"
#include "wave.h"
#include "sphere.h"
#include "vec3fSpherical.h"

#include <cmath>

#include "opengl.h"

class Defence3D
{
public:
    Defence3D(vec3f location, vec3fSpherical sphr, float creationTime);

    void draw(Wave3D *wave);
    void drawDot(float x, float y, float z);

    void updateProjectileState(float dt);

    vec3f getLocation();
    float getRadius();

    bool collision(vec3f otherLocation, float otherRadius);

    void increaseRadius();
    int time = 0;

private:
    vec3f location;
    vec3fSpherical spherical;
    float creationTime;

    vec3f r0 = {0.0, 0.0, 0.0}; // Initial position
    vec3f v0 = {0.0, 0.0, 0.0}; // Initial velocity
    vec3f r = {0.0, 0.0, 0.0};  // Drawn position
    vec3f v = {0.0, 0.0, 0.0};  // Drawn velocity

    float g = -0.25;

    float radius = 0.02;
};

#endif // THREE_D_DEFENCE_H