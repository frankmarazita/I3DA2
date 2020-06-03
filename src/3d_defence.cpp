#include "3d_defence.h"

Defence3D::Defence3D(vec3f location, vec3fSpherical spherical, float creationTime)
{
    this->location = location;
    this->spherical = spherical;
    this->creationTime = creationTime;

    r0 = location;
    v0 = sphericalToCartesian(spherical);
    r = location;
    v = v0;
}

void Defence3D::drawDot(float x, float y, float z)
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glTranslated(location.x, location.y, location.z);
    glutWireSphere(radius, 8, 8);
    glPopMatrix();
}

void Defence3D::draw(Wave3D *wave)
{
    // Draw Projectile
    glColor3f(1, 1, 1);
    drawDot(r.x, r.y, r.z);

    // Draw Trajectory Curve
    vec3f rTemp = r;
    vec3f vTemp = v;

    float t = 0.01;
    // Wave intersection
    float y = wave->getYfromXZ(rTemp.x, 0.0);
    glBegin(GL_LINE_STRIP);
    vec3f rotated;
    while (rTemp.y > y)
    {
        rTemp.x += vTemp.x * t;
        rTemp.y += vTemp.y * t;
        rTemp.z += vTemp.z * t;
        vTemp.y += g * t;

        glVertex3f(rTemp.x, rTemp.y, rTemp.z);
        y = wave->getYfromXZ(rTemp.x, rTemp.z);
    }
    glEnd();
}

void Defence3D::updateProjectileState(float dt)
{
    // Update projectile values and location
    r.x += v.x * dt;
    r.y += v.y * dt;
    r.z += v.z * dt;
    v.y += g * dt;

    location = {r.x, r.y, r.z};
}

vec3f Defence3D::getLocation()
{
    return location;
}

float Defence3D::getRadius()
{
    return radius;
}

bool Defence3D::collision(vec3f otherLocation, float otherRadius)
{
    float dist = calcVectorDistance(otherLocation, location);
    if (dist <= radius + otherRadius)
        return true;
    return false;
}

void Defence3D::increaseRadius()
{
    // Grow defence size based on time
    radius = 0.0001 * (this->time - creationTime);
}