#ifndef EFFECT_H
#define EFFECT_H

#include "vec3f.h"
#include "vec3fSpherical.h"
#include "particle.h"
#include "random.h"

#include <vector>

#include "opengl.h"

class Effect
{
public:
    Effect(vec3f location, int creationTime);
    ~Effect();

    void generateParticles();

    void draw();
    void update(float dt);

    int getNumParticles();

    int time = 0;

private:
    Random *random = new Random();

    const int numParticles = 50;
    int creationTime;

    vec3f location;
    std::vector<Particle *> particles;
};

#endif // EFFECT_H