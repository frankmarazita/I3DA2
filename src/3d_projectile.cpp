#include "3d_projectile.h"

Projectile3D::Projectile3D(vec3f location, vec3fSpherical spherical, bool isBoat, int boatNum)
{
    this->location = location;
    this->spherical = spherical;
    this->isBoat = isBoat;
    this->boatNum = boatNum;

    r0 = location;
    v0 = sphericalToCartesian(spherical);
    r = location;
    v = v0;
}

// In place of a sphere for now
void Projectile3D::drawDot(float x, float y, float z)
{
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex3f(x, y, z);
    glEnd();
    glPopMatrix();
}

void Projectile3D::draw(Wave3D *wave)
{
    int numSegments = 100;

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

void Projectile3D::updateProjectileState(float dt)
{
    // Update projectile values and location
    r.x += v.x * dt;
    r.y += v.y * dt;
    r.z += v.z * dt;
    v.y += g * dt;

    location = {r.x, r.y, r.z};
}

vec3f Projectile3D::getLocation()
{
    return location;
}

bool Projectile3D::getCollision(float radius, vec2f location)
{
    float dx = this->location.x - location.x;
    float dy = this->location.y - location.y;
    float distance = sqrt(pow(dx, 2) + pow(dy, 2));
    // Check projectile collision with other based on radius
    if (distance < radius + this->radius)
        return true;
    return false;
}

bool Projectile3D::getIsBoat()
{
    // Return projectile creation object
    return isBoat;
}

int Projectile3D::getBoatNum()
{
    return boatNum;
}