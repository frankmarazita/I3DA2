#ifndef PARTICLE_H
#define PARTICLE_H

#include "vec3f.h"
#include "vec3fSpherical.h"
#include "particle.h"
#include "functions.h"

#include <vector>

#include "opengl.h"

class Particle
{
public:
    Particle(vec3f location, vec3fSpherical spherical, int decay);

    void draw();
    void update(float dt);

    int getDecay();

private:
    vec3f location;
    vec3fSpherical spherical;
    int decay;

    vec3f r0 = {0.0, 0.0, 0.0}; // Initial position
    vec3f v0 = {0.0, 0.0, 0.0}; // Initial velocity
    vec3f r = {0.0, 0.0, 0.0};  // Drawn position
    vec3f v = {0.0, 0.0, 0.0};  // Drawn velocity

    float g = -0.25;

    float scale = 0.01;
};

#endif // PARTICLE_H