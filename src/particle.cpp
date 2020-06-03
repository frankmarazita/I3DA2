#include "particle.h"

Particle::Particle(vec3f location, vec3fSpherical spherical, int decay)
{
    this->location = location;
    this->spherical = spherical;
    this->decay = decay;

    r0 = location;
    v0 = sphericalToCartesian(spherical);
    r = location;
    v = v0;
}

void Particle::draw()
{
    glPushMatrix();
    glColor3f(1.0, 0, 0);
    glTranslated(location.x, location.y, location.z);
    glScalef(scale, scale, scale);
    glutSolidCube(1.0);
    glPopMatrix();
}

void Particle::update(float dt)
{
    // Update projectile values and location
    r.x += v.x * dt;
    r.y += v.y * dt;
    r.z += v.z * dt;
    v.y += g * dt;

    location = {r.x, r.y, r.z};
}

int Particle::getDecay()
{
    return decay;
}