#include "3d_boat.h"

Boat3D::Boat3D(vec3f location, float boatDeg, float boatRotation, float cannonDeg)
{
    this->location = location;
    this->boatDeg = boatDeg;
    this->boatRotation = boatRotation;
    this->projectilePolar.angle = cannonDeg;
    this->initialCannonDeg = cannonDeg;
}

Projectile3D *Boat3D::shoot()
{
    // Check for projectile shoot cooldown
    if (this->time - shootTime >= cooldownTime)
    {
        shootTime = this->time;

        // Create a new projectile and return it
        Projectile3D *projectile = new Projectile3D(projectileOrigin, sphericalVec, true, 0);
        return projectile;
    }
    return NULL;
}

void Boat3D::draw()
{
    glPushMatrix();

    glTranslatef(this->location.x, this->location.y, this->location.z);
    glScalef(scale, scale, scale);
    glRotatef(boatRotation, 0, 1, 0);
    glRotatef(boatDeg, 0, 0, 1);

    // Hitbox
    // glColor4f(1, 1, 1, 1);
    // glutSolidSphere(hitboxRadius, 10, 10);

    glColor4f(col.r, col.g, col.b, col.a);

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
    glRotatef(-90 + projectilePolar.angle, 0.0, 0.0, 1.0);
    Cylinder *cylinder = new Cylinder(0.1, 0.7, 8);
    cylinder->draw();
    glPopMatrix();

    glPopMatrix();
}

vec3f Boat3D::getLocation()
{
    return this->location;
}

vec3f Boat3D::getPrevLocation()
{
    return this->prevLocation;
}

void Boat3D::setLocation(vec3f location)
{
    this->location = location;
}

void Boat3D::setPrevLocation()
{
    this->prevLocation = this->location;
}

void Boat3D::setBoatRotation(float boatRotation)
{
    this->boatRotation = boatRotation;
    sphericalVec.polar = boatRotation;
}

void Boat3D::updateBoatRotation()
{
    float destX = 0;
    float destZ = 0;

    float grad = calcGrad(this->location.x, this->location.z, destX, destZ);
    float rad = gradToRad(grad);
    float deg = radToDeg(rad);

    if (destX > this->location.x)
    {
        this->boatRotation = -deg;
        sphericalVec.polar = boatRotation;
    }
    else if (destX < this->location.x)
    {
        this->boatRotation = 180 - deg;
        sphericalVec.polar = boatRotation;
    }
}

void Boat3D::setBoatDeg(float boatDeg)
{
    this->boatDeg = boatDeg;
}

float Boat3D::getInitialCannonDeg()
{
    return initialCannonDeg;
}

float Boat3D::getCannonDeg()
{
    return projectilePolar.angle;
}

void Boat3D::setCannonDeg(float cannonDeg)
{
    this->projectilePolar.angle = cannonDeg;
}

float Boat3D::getHitboxRadius()
{
    return hitboxRadius * scale;
}

void Boat3D::calcBoatDegFromPrev()
{
    float grad = calcVectorGrad(prevLocation, location);
    this->boatDeg = gradToDeg(grad);
}

void Boat3D::calcProjectileOrigin()
{
    float radCannon = degToRad(projectilePolar.angle);
    float radBoat = degToRad(boatDeg);
    float radRotation = degToRad(boatRotation);

    vec3f cannonOrigin = {0.35, 0.25, 0};
    vec3f cannonExit = {1.05, 0.25, 0};

    cannonExit = rotatePointZ(cannonOrigin, cannonExit, radCannon);
    cannonExit = rotatePointZ({0, 0, 0}, cannonExit, radBoat);
    cannonExit = rotatePointY({0, 0, 0}, cannonExit, radRotation);
    cannonExit = {cannonExit.x * scale, cannonExit.y * scale, cannonExit.z * scale};
    cannonExit = {cannonExit.x + this->location.x, cannonExit.y + this->location.y, cannonExit.z + this->location.z};

    projectileOrigin = cannonExit;
}

vec3f Boat3D::getProjectileOrigin()
{
    return projectileOrigin;
}

bool Boat3D::collision(vec3f otherLocation, float otherRadius)
{
    float dist = calcVectorDistance(otherLocation, location);
    if (dist <= hitboxRadius * scale + otherRadius)
        return true;
    return false;
}