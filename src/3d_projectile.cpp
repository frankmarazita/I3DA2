#include "3d_projectile.h"

Projectile3D::Projectile3D(vec3f location, vec3fSpherical spherical, bool isBoat, int segments)
{
    this->location = location;
    this->spherical = spherical;
    this->isBoat = isBoat;

    r0 = location;
    v0 = sphericalToCartesian(spherical);
    r = location;
    v = v0;
    this->sphere = new Sphere(radius, segments, segments);
}

void Projectile3D::drawDot(float x, float y, float z)
{
    glPushMatrix();
    glColor3f(0.3, 0.3, 1.0);
    glTranslated(location.x, location.y, location.z);
    sphere->draw();
    glPopMatrix();
}


void Projectile3D::draw(Wave3D *wave)
{
    // Draw Projectile
    drawDot(r.x, r.y, r.z);
    // Draw Trajectory Curve, if boat
    if (isBoat) {
        vec3f rTemp = r;
        vec3f vTemp = v;

        float t = 0.01;
        // Wave intersection
        float y = wave->getYfromXZ(rTemp.x, 0.0);
        glDisable(GL_LIGHTING);
        glColor3f(0.0, 1.0, 1.0);
        glBegin(GL_LINE_STRIP);
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
        glEnable(GL_LIGHTING);
    }
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

float Projectile3D::getRadius()
{
    return radius;
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
    return isBoat;
}