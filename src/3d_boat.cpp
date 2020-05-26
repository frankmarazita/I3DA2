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
    // glRotatef(-90, 1.0, 0, 0);
    glutSolidSphere(0.05, 10, 10);
    glPopMatrix();
}