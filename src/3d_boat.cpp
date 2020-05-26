#include "3d_boat.h"

Boat3D::Boat3D(vec3f location, float boatDeg, float cannonDeg)
{
    this->location = location;
    this->boatDeg = boatDeg;
    this->projectilePolar.angle = cannonDeg;
}

void Boat3D::draw()
{
    glPushMatrix();
    glColor4f(col.r, col.g, col.b, col.a);
    glTranslatef(this->location.x, this->location.y, this->location.z);
    glRotatef(this->boatDeg, 0, 0, 1);
    glRotatef(-this->boatRotation, 0, 1, 0);
    // glutSolidSphere(0.05, 6, 6);
    glutSolidTeapot(0.05);
    glPopMatrix();
}

vec3f Boat3D::getLocation()
{
    return this->location;
}

void Boat3D::setLocation(vec3f location)
{
    this->location = location;
}

void Boat3D::setBoatRotation(float boatRotation)
{
    this->boatRotation = boatRotation;
}

void Boat3D::updateBoatRotation()
{
    // TODO Calc boat rotation based on location and relative destination
}

void Boat3D::setBoatDeg(float boatDeg)
{
    this->boatDeg = boatDeg;
}