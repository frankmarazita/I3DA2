#include "effect.h"

Effect::Effect(vec3f location, int creationTime)
{
    this->location = location;
    this->creationTime = creationTime;
    generateParticles();
}

Effect::~Effect()
{
    delete random;
}

void Effect::generateParticles()
{
    for (int i = 0; i < numParticles; i++)
    {
        float magnitude = (float)random->getRandom(25, 35) * 0.01;
        float angle = (float)random->getRandom(35, 80);
        float rotation = (float)random->getRandom(0, 360);
        int decay = random->getRandom(1000, 3000);

        vec3fSpherical spherical = {magnitude, angle, rotation};
        Particle *p = new Particle(location, spherical, decay);

        particles.push_back(p);
    }
}

void Effect::draw()
{
    for (int i = 0; i < particles.size(); i++)
    {
        Particle *particle = particles[i];
        particle->draw();
    }
}

void Effect::update(float dt)
{
    for (int i = 0; i < particles.size(); i++)
    {
        Particle *particle = particles[i];
        particle->update(dt);
    }

    for (int i = 0; i < particles.size(); i++)
    {
        Particle *particle = particles[i];
        if (particle->getDecay() + creationTime < time)
        {
            particles.erase(particles.begin() + i);
            delete particle;
            break;
        }
    }
}

int Effect::getNumParticles()
{
    return particles.size();
}