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
	float x = -10.0;
	float z = 10.0;

	float dist = 2 * z / numSegments;
	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_TRIANGLE_STRIP);
	for (int i = 0; i < numSegments; i++)
	{
		if (i % 2 == 0)
		{
			for (int j = 0; j <= numSegments; j++)
			{
				float px = x + j * dist;
				glNormal3f(px, sin(px), z - i * dist);
				glVertex3f(px, sin(px), z - i * dist);
				glNormal3f(px, sin(px), z - i * dist - dist);
				glVertex3f(px, sin(px), z - i * dist - dist);
			}
		}
		else
		{
			for (int j = numSegments; j >= 0; j--)
			{
				float px = x + j * dist;
				glNormal3f(px, sin(px), z - i * dist);
				glVertex3f(px, sin(px), z - i * dist);
				glNormal3f(px, sin(px), z - i * dist - dist);
				glVertex3f(px, sin(px), z - i * dist - dist);
			}
		}
	}
	glEnd();
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
		verticies.push_back({ x, y });
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

	float x2 = 0;
	float y2 = 0;

	// Calculate Normals and Tangents
	if (normalize)
	{
		glColor3f(0, 1, 0);

		m = -(1 / m);
		if (m < 0)
		{
			x2 = x - cos(gradToRad(m)) * s;
			y2 = y - sin(gradToRad(m)) * s;
		}
		else
		{
			x2 = x + cos(gradToRad(m)) * s;
			y2 = y + sin(gradToRad(m)) * s;
		}
	}
	else
	{
		glColor3f(1, 0, 0);

		if (m < 0)
		{
			x2 = x - cos(gradToRad(m)) * s;
			y2 = y - sin(gradToRad(m)) * s;
		}
		else
		{
			x2 = x + cos(gradToRad(m)) * s;
			y2 = y + sin(gradToRad(m)) * s;
		}
	}

	// Draw Normals and Tangents
	glBegin(GL_LINE_STRIP);
	if (z)
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