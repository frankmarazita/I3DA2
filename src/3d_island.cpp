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
    glTranslatef(location.x, location.y, location.z);
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

void Island3D::drawHealth()
{
    float x = -0.95 + 0.005 * 100;
    glPushMatrix();
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_LOOP);
    glVertex2f(-0.95, 0.95);
    glVertex2f(-0.95, 0.92);
    glVertex2f(x, 0.92);
    glVertex2f(x, 0.95);
    glEnd();
    glPopMatrix();

    x = -0.95 + 0.005 * health;
    glPushMatrix();
    glColor3f(0, 1, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-0.95, 0.95);
    glVertex2f(-0.95, 0.92);
    glVertex2f(x, 0.92);
    glVertex2f(x, 0.95);
    glEnd();
    glPopMatrix();
}

void Island3D::drawScore()
{
    glPushMatrix();
    std::string text = "Score: " + std::to_string((int)score);
    int len = text.length();
    glTranslatef(-0.95, 0.86, 0.0);
    glColor3f(1, 1, 0);
    glRasterPos2f(0, 0);
    for (int i = 0; i < len; i++)
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text[i]);
    glPopMatrix();
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
    if (cannonPitch + CANNON_TILT_SPEED < CANNON_TILT_MIN)
    {
        printf("RETURNEDDD");
        return;
    }

    cannonPitch -= CANNON_TILT_SPEED;
}

bool Island3D::collision(vec3f otherLocation, float otherRadius)
{
    float dist = calcVectorDistance(otherLocation, location);
    if (dist <= radius + otherRadius)
        return true;
    return false;
}