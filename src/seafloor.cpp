#include "seafloor.h"

Seafloor::Seafloor(float windowSize) // Make it use windowSize instead of -1.0 to 1.0..?
{
	this->windowSize = windowSize;
	this->texture = new Texture("../src/sand.jpg");
}

void Seafloor::draw()
{
	texture->enable();
	glColor3f(0.8f, 0.8f, 0.8f);

	// Maybe -1.0 for height is too low
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0);
	glVertex3f(-1.0, -1.0, 1.0);
	glTexCoord2f(1, 0);
	glVertex3f(1.0, -1.0, 1.0);
	glTexCoord2f(1, 1);
	glVertex3f(1.0, -1.0, -1.0);
	glTexCoord2f(0, 1);
	glVertex3f(-1.0, -1.0, -1.0);
	glEnd();

	texture->disable();
}