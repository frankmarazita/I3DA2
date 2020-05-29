#include "3d_island.h"

Island3D::Island3D()
{
    this->texture = new Texture("../src/sand.jpg");
	this->cannon = new Cylinder(0.04, 0.19, 64);
    this->cannonBaseMiddle = new Cylinder(0.1, 0.25, 64);
    this->cannonGunBaseCylinder = new Cylinder(0.05, 0.15, 64);
}

void Island3D::draw()
{
    texture->enable();

    glColor3f(0.9, 0.8, 0.5);

    // Very very bottom cylinder
    glPushMatrix();
    glTranslatef(0, -1, 0);
    glRotatef(-90, 1.0, 0, 0);

    GLUquadric *qobj = gluNewQuadric();
    gluCylinder(qobj, radius, radius, 0.5, 40, 40);
    glPopMatrix();

    // Sphere
    glColor3f(0.8, 0.8, 0.8);
    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    glRotatef(-90, 1.0, 0, 0);
    glutSolidSphere(radius, 40, 40);
    glPopMatrix();

    // Cylinder Base (Middle)
    glPushMatrix();
    glTranslatef(0, -0.49, 0);
    cannonBaseMiddle->draw();
    glPopMatrix();

    // Cylinder Base (Gun Base)
    /*glPushMatrix();
    glTranslatef(0, -0.20, 0);
    //glRotatef(90, 0.0, 0, 1.0);
    glRotatef(cannonRotation, 0.0, 1.0, 0.0);
    //glRotatef(-90, 1.0, 0, 0);
    cannonGunBaseCylinder->draw();
    glPopMatrix();*/

	// Cannon
	glPushMatrix();
    glTranslatef(0, -0.2, 0);
    // Rotation
    glRotatef(cannonRotation, 0.0, 1.0, 0.0);
    // Pitch
    glRotatef(cannonPitch, 0.0, 0.0, 1.0);

    cannon->draw();
	glPopMatrix();

    texture->disable();
}

void Island3D::tiltCannonUp()
{
    if (cannonPitch + CANNON_TILT_SPEED > CANNON_TILT_MAX)
        return;
    
    cannonPitch += CANNON_TILT_SPEED;
}

void Island3D::tiltCannonDown()
{
    printf("%f %f\n", cannonPitch, cannonPitch + CANNON_TILT_SPEED);
    if (cannonPitch + CANNON_TILT_SPEED < CANNON_TILT_MIN) {
        printf("RETURNEDDD");
        return;
    }

    cannonPitch -= CANNON_TILT_SPEED;
}

bool Island3D::collision(vec3f location)
{
    float dist = calcVectorDistance(location, {0, -0.5, 0});
    if (dist <= radius)
        return true;
    return false;
}