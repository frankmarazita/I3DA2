#include "3d_wave.h"

Wave3D::Wave3D(float windowSize, float numSegments, float a, float b, float c, float d)
{
	this->windowSize = windowSize;
	this->numSegments = numSegments;
	this->segmentSize = windowSize * 2 / numSegments;

	this->a = a;
	this->b = b;
	this->c = c;
	this->d = d;

	calcVerticies();
}

void Wave3D::draw()
{
	this->setLighting();
	float x = -1.0;
	float z = 1.0;

	float dist = 2 * z / numSegments;
	glColor4f(col.r, col.g, col.b, col.a);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < numSegments; i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j <= numSegments; j++)
			{
				float px = x + j * dist;
				glNormal3f(px, getYfromX(px), z - i * dist);
				glVertex3f(px, getYfromX(px), z - i * dist);
				glNormal3f(px, getYfromX(px), z - i * dist - dist);
				glVertex3f(px, getYfromX(px), z - i * dist - dist);
			}
		}
		else
		{
			for (int j = numSegments; j >= 0; j--)
			{
				float px = x + j * dist;
				glNormal3f(px, getYfromX(px), z - i * dist);
				glVertex3f(px, getYfromX(px), z - i * dist);
				glNormal3f(px, getYfromX(px), z - i * dist - dist);
				glVertex3f(px, getYfromX(px), z - i * dist - dist);
			}
		}
	}
	glEnd();

	this->disableLighting();
}

void Wave3D::setLighting()
{
	glBlendFunc(GL_ONE, GL_ONE); // Enables Transparency
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	GLfloat light_ambient[] = {0.2, 0.5, 1.0, 0.75};
	GLfloat light_diffuse[] = {0.2, 0.5, 1.0, 0.75};
	GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
	GLfloat mat_specular[] = {0.2, 0.5, 1.0, 0};
	GLfloat high_shininess[] = {100.0};
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	// glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
	// glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
}

void Wave3D::disableLighting()
{
	glDisable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}

float Wave3D::getGradientForSine(float x)
{
	return a * b * cosf(b * x + c);
}

void Wave3D::drawTom()
{
	this->setLighting();
	float left = -1.0;
	float right = 1.0;
	float range = right - left;

	float x, y, z;

	float xStep;
	// drawSine(0.25, 2.0 * M_PI, 1.0, 1.0, 100.0);
	// findYForSine(0.25, 2.0 * M_PI, 1.0, x, 1.0);

	float step_size = range / numSegments;
	for (int i = 0; i < numSegments; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		z = right - i * step_size;
		for (int j = 0; j < numSegments; j++)
		{
			x = left + j * step_size;
			y = getYfromX(x);
			glNormal3f(x, y, z);
			//glTexCoord2f(0, 0);
			glVertex3f(x, y, z);
			//glTexCoord2f(1, 0);
			glNormal3f(x, y, z - step_size);
			//glTexCoord2f(1, 1);
			//glTexCoord2f(0, 1);
			glVertex3f(x, y, z - step_size);
		}
		glEnd();
	}
	this->disableLighting();

	// Vectors
	if (normal || tangent)
	{
		for (int i = 0; i < numSegments; i++)
		{
			z = right - i * step_size;
			for (int j = 0; j < numSegments; j++)
			{
				x = left + j * step_size;
				y = getYfromX(x);
				float m = getGradientForSine(x);
				glColor3f(1.0, 1.0, 0.0);
				if (normal)
					drawVector({x, y, z}, m, 0.1, true);
				if (tangent)
					drawVector({x, y, z}, m, 0.1, false);
			}
		}
	}
}

void Wave3D::drawTom2()
{
	this->setLighting();
	float left = -1.0;
	float right = 1.0;
	float range = right - left;

	float x, y, z;

	float xStep;
	// drawSine(0.25, 2.0 * M_PI, 1.0, 1.0, 100.0);
	// findYForSine(0.25, 2.0 * M_PI, 1.0, x, 1.0);

	float step_size = range / numSegments;
	for (int i = 0; i < numSegments; i++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		z = right - i * step_size;
		for (int j = 0; j < numSegments; j++)
		{
			x = left + j * step_size;
			y = getYfromX(x);
			glNormal3f(x, y, z);
			glVertex3f(x, y, z);
			glNormal3f(x, y, z - step_size);
			glVertex3f(x, y, z - step_size);
		}
		glEnd();
	}
	this->disableLighting();

	// Vectors
	if (normal || tangent)
	{
		for (int i = 0; i < numSegments; i++)
		{
			z = right - i * step_size;
			for (int j = 0; j < numSegments; j++)
			{
				x = left + j * step_size;
				y = getYfromX(x);
				float m = getGradientForSine(x);
				glColor3f(1.0, 1.0, 0.0);
				if (normal)
					drawVector({x, y, z}, m, 0.1, true);
				if (tangent)
					drawVector({x, y, z}, m, 0.1, false);
			}
		}
	}
}

void Wave3D::moveWave(float amount)
{
	// Set the wave displacement c value
	c = amount;
}

void Wave3D::calcVerticies()
{
	verticies.clear();
	// Calculate the initial verticies locations based on num segments
	for (int i = 0; i <= numSegments; i++)
	{
		float x = -windowSize + segmentSize * i;
		float y = a * sin(b * x + c) + d;
		verticies.push_back({x, y});
	}
}

float Wave3D::getYfromX(float x)
{
	return a * sin(b * x + c) + d;
}

float Wave3D::getGrad(float x)
{
	return radToDeg(a * b * cosf(b * x + c) / (M_PI / 2));
}

bool Wave3D::getAnimate()
{
	return animate;
}

int Wave3D::getNumSegments()
{
	return numSegments;
}

void Wave3D::toggleNormal()
{
	normal = !normal;
}

void Wave3D::toggleTangent()
{
	tangent = !tangent;
}

void Wave3D::toggleAnimation()
{
	animate = !animate;
}

void Wave3D::increaseNumSegments()
{
	numSegments *= 2;
	segmentSize = windowSize * 2 / numSegments;
	calcVerticies();
}

void Wave3D::decreaseNumSegments()
{
	// Halve the number of segments
	int newNumSegments = numSegments / 2;
	// Check for minimum 4
	if (newNumSegments >= 4)
	{
		numSegments = newNumSegments;
		segmentSize = windowSize * 2 / numSegments;
		// Recalulate verticies
		calcVerticies();
	}
}

void Wave3D::drawVector(vec3f point, float m, float s, bool normalize)
{
	float x = point.x;
	float y = point.y;
	float z = point.z;

	float x2 = 0.0;
	float y2 = 0.0;

	if (normalize)
	{
		glColor3f(0.0, 1.0, 0.0);
		m = -(1 / m);
	}
	else
	{
		glColor3f(1.0, 0.0, 0.0);
	}

	if (m < 0)
	{
		x2 = x - cos(atan(m)) * s;
		y2 = y - sin(atan(m)) * s;
	}
	else
	{
		x2 = x + cos(atan(m)) * s;
		y2 = y + sin(atan(m)) * s;
	}

	glBegin(GL_LINE_STRIP);
	if (!z)
	{
		glVertex2f(x, y);
		glVertex2f(x2, y2);
	}
	else
	{
		glVertex3f(x, y, z);
		glVertex3f(x2, y2, z);
	}
	glEnd();
}