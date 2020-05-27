#include "3d_boat.h"

Boat3D::Boat3D(vec3f location, float boatDeg, float boatRotation, float cannonDeg)
{
    this->location = location;
    this->boatDeg = boatDeg;
    this->boatRotation = boatRotation;
    this->projectilePolar.angle = cannonDeg;
}

void Boat3D::draw()
{
    glColor4f(col.r, col.g, col.b, col.a);

    glPushMatrix();

    glTranslatef(this->location.x, this->location.y, this->location.z);
    glScalef(scale, scale, scale);
    glRotatef(boatDeg, 0, 0, 1);
    glRotatef(boatRotation, 0, 1, 0);

    // Draw Hull
    glBegin(GL_QUADS);
    // Top
    glVertex3f(1.0, 0.3, -0.7);
    glVertex3f(-1.0, 0.3, -0.7);
    glVertex3f(-1.0, 0.3, 0.7);
    glVertex3f(1.0, 0.3, 0.7);
    // Bottom
    glVertex3f(0.5, -0.3, 0.7);
    glVertex3f(-0.5, -0.3, 0.7);
    glVertex3f(-0.5, -0.3, -0.7);
    glVertex3f(0.5, -0.3, -0.7);
    // Front
    glVertex3f(1.0, 0.3, -0.7);
    glVertex3f(-1.0, 0.3, -0.7);
    glVertex3f(-0.5, -0.3, -0.7);
    glVertex3f(0.5, -0.3, -0.7);
    // Back
    glVertex3f(1.0, 0.3, 0.7);
    glVertex3f(-1.0, 0.3, 0.7);
    glVertex3f(-0.5, -0.3, 0.7);
    glVertex3f(0.5, -0.3, 0.7);
    // Left
    glVertex3f(-1.0, 0.3, 0.7);
    glVertex3f(-1.0, 0.3, -0.7);
    glVertex3f(-0.5, -0.3, -0.7);
    glVertex3f(-0.5, -0.3, 0.7);
    // Right
    glVertex3f(1.0, 0.3, 0.7);
    glVertex3f(1.0, 0.3, -0.7);
    glVertex3f(0.5, -0.3, -0.7);
    glVertex3f(0.5, -0.3, 0.7);
    glEnd();

    // Draw Bridge
    glBegin(GL_QUADS);
    // Top
    glVertex3f(0.35, 0.95, 0.35);
    glVertex3f(-0.35, 0.95, 0.35);
    glVertex3f(-0.35, 0.95, -0.35);
    glVertex3f(0.35, 0.95, -0.35);
    // Front
    glVertex3f(0.35, 0.95, -0.35);
    glVertex3f(-0.35, 0.95, -0.35);
    glVertex3f(-0.35, 0.3, -0.35);
    glVertex3f(0.35, 0.3, -0.35);
    // Back
    glVertex3f(0.35, 0.95, 0.35);
    glVertex3f(-0.35, 0.95, 0.35);
    glVertex3f(-0.35, 0.3, 0.35);
    glVertex3f(0.35, 0.3, 0.35);
    // Left
    glVertex3f(-0.35, 0.95, 0.35);
    glVertex3f(-0.35, 0.95, -0.35);
    glVertex3f(-0.35, 0.3, -0.35);
    glVertex3f(-0.35, 0.3, 0.35);
    // Right
    glVertex3f(0.35, 0.95, 0.35);
    glVertex3f(0.35, 0.95, -0.35);
    glVertex3f(0.35, 0.3, -0.35);
    glVertex3f(0.35, 0.3, 0.35);
    glEnd();

    // Draw Cannon
    glPushMatrix();
    glTranslatef(0.35, 0.25, 0.0);
    glRotatef(projectilePolar.angle, 0.0, 0.0, 1.0);
    glBegin(GL_QUADS);
    // Top
    glVertex3f(0.7, 0.1, 0.1);
    glVertex3f(0, 0.1, 0.1);
    glVertex3f(0, 0.1, -0.1);
    glVertex3f(0.7, 0.1, -0.1);
    // Bottom
    glVertex3f(0.7, -0.1, 0.1);
    glVertex3f(0, -0.1, 0.1);
    glVertex3f(0, -0.1, -0.1);
    glVertex3f(0.7, -0.1, -0.1);
    // Front
    glVertex3f(0.7, 0.1, -0.1);
    glVertex3f(0, 0.1, -0.1);
    glVertex3f(0, -0.1, -0.1);
    glVertex3f(0.7, -0.1, -0.1);
    // Back
    glVertex3f(0.7, 0.1, 0.1);
    glVertex3f(0, 0.1, 0.1);
    glVertex3f(0, -0.1, 0.1);
    glVertex3f(0.7, -0.1, 0.1);
    // Right
    glVertex3f(0.7, 0.1, 0.1);
    glVertex3f(0.7, 0.1, -0.1);
    glVertex3f(0.7, -0.1, -0.1);
    glVertex3f(0.7, -0.1, 0.1);
    glEnd();
    glPopMatrix();
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
    float destX = 0;
    float destZ = 0;

    float grad = calcGrad(this->location.x, this->location.z, destX, destZ);
    float rad = gradToRad(grad);
    float deg = radToDeg(rad);

    if (destX > this->location.x)
        this->boatRotation = -deg;
    else if (destX < this->location.x)
        this->boatRotation = 180 - deg;
}

void Boat3D::setBoatDeg(float boatDeg)
{
    this->boatDeg = boatDeg;
}