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
    gluCylinder(qobj, 0.25, 0.25, 0.5, 40, 40);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0, -0.5, 0);
    glRotatef(-90, 1.0, 0, 0);
    glutSolidSphere(0.25, 40, 40);
    glPopMatrix();

    texture->disable();
}