#include "cylinder.h"

Cylinder::Cylinder(float radius, float height, float segments)
{
	this->radius = radius;
	this->height = height;
	this->segments = segments;
}

void Cylinder::draw()
{
	float x, y, z;
	float theta;

	//glColor3f(1.0, 0.0, 0.0);
	// Bottom
	glBegin(GL_POLYGON);
	for (int i = 0; i < segments + 1; i++)
    {
		theta = i / (float)segments * 2.0 * M_PI;
		x = radius * cosf(theta);
		z = radius * sinf(theta);
        glNormal3f(x, -height/2, z);
		glVertex3f(x, -height / 2, z);
	}
	glEnd();

	// Walls
	//glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_QUAD_STRIP);

    float texInc = radius * 1.0f / segments;

	for (int i = 0; i < segments + 1; i++)
    {
		theta = i / (float)segments * 2.0 * M_PI;
		x = radius * cosf(theta);
		z = radius * sinf(theta);
        float s = theta / 2.0 * M_PI;
        float t = (z + height / 2) / height;
        //printf("%f %f\n", s, t);
        glTexCoord2f(i, height/2);
        glTexCoord2f(i, -height/2);
        glNormal3f(x, height/2, z);
		glVertex3f(x, height/2, z);
        glNormal3f(x, -height / 2, z);
		glVertex3f(x, -height / 2, z);
	}
	glEnd();

	// Top
	//glColor3f(0.0, 0.0, 1.0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < segments + 1; i++)
    {
		theta = i / (float)segments * 2.0 * M_PI;
		x = radius * cosf(theta);
		z = radius * sinf(theta);
        glNormal3f(x, height/2, z);
		glVertex3f(x, height/2, z);
	}
	glEnd();
}
