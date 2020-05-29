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

	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(2.0);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < segments; i++) {
		theta = i / (float)segments * 2.0 * M_PI;
		x = radius * cosf(theta);
		z = radius * sinf(theta);
		glVertex3f(x, 0, z);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (int i = 0; i < segments + 1; i++) {
		theta = i / (float)segments * 2.0 * M_PI;
		x = radius * cosf(theta);
		z = radius * sinf(theta);
		glVertex3f(x, height, z);
		glVertex3f(x, 0, z);
	}
	glEnd();
}
