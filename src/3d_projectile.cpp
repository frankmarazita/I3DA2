#include "3d_projectile.h"

Projectile3D::Projectile3D(vec3f location, vec3fSpherical spherical, bool isBoat, int boatNum)
{
    this->location = location;
    this->spherical = spherical;
    this->isBoat = isBoat;
    this->boatNum = boatNum;

    r0 = location;
    v0 = sphericalToCartesian(spherical);

    printf("OLD velocity cartesian: %f %f %f\n", v0.x, v0.y, v0.z);
    v0 = rotatePointY({ 0.0, 0.0, 0.0 }, v0, degToRad(spherical.polar));
    printf("NEW velocity cartesian: %f %f %f\n", v0.x, v0.y, v0.z);

    r = location;
    v = v0;

    printf("velocity spherical: mag: %f, a: %f, polar: %f\n", spherical.magnitude, spherical.a, spherical.polar);
    printf("velocity cartesian: %f %f %f\n", v0.x, v0.y, v0.z);
}

void Projectile3D::dradwDot(float x, float y, float z)
{
    glPushMatrix();
    //vec3f draw = rotatePointY(r0, r, degToRad(spherical.polar));
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
    /*glBegin(GL_POLYGON);
    for (int i = 0; i < numSegments; i++)
    {
        float theta = 2.0 * M_PI * float(i) / float(numSegments);
        float x1 = cos(theta) * radius;
        float y1 = sin(theta) * radius;
        glVertex2f(x1 + r.x, y1 + r.y);
    }
    glEnd();*/

    // Draw Trajectory Curve
    vec3f rTemp = r;
    vec3f vTemp = v;

    dradwDot(rTemp.x, rTemp.y, rTemp.z);
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
        //printf("R TEMP Z %f\n", rTemp.z);
        vTemp.y += g * t;

        //rTemp.z = r0.z;

        //rotated = rotatePointY(r0, rTemp, degToRad(spherical.polar));
        //glVertex3f(rotated.x, rotated.y, rotated.z);
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