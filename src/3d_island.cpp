#include "3d_island.h"

Island3D::Island3D()
{
    this->texture = new Texture("../src/sand.jpg");
}

void Island3D::draw()
{
    texture->enable();

    glColor3f(0.9, 0.8, 0.5);

    glPushMatrix();
    glTranslatef(0, -1, 0);
    glRotatef(-90, 1.0, 0, 0);
    GLUquadric *qobj = gluNewQuadric();
    /*
	gluQuadricDrawStyle(this->qobj, GLU_FILL);
	gluQuadricTexture(this->qobj, GL_TRUE);
	gluQuadricNormals(this->qobj, GLU_SMOOTH);
	*/
    gluCylinder(qobj, radius, radius, 0.5, 40, 40);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(location.x, location.y, location.z);
    glRotatef(-90, 1.0, 0, 0);
    glutSolidSphere(radius, 40, 40);
    glPopMatrix();

    // Cannon
    glPushMatrix();

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

bool Island3D::collision(vec3f otherLocation, float otherRadius)
{
    float dist = calcVectorDistance(otherLocation, location);
    if (dist <= radius + otherRadius)
        return true;
    return false;
}