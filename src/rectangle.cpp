#include "rectangle.h"

Rectangle3D::Rectangle3D(float length, float width, float depth)
{
    this->length = length;
    this->depth = depth;
    this->width = width;
}

void Rectangle3D::draw()
{
    float x, y, z;

    // Walls
    //glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_QUADS);

    glColor3f(0.0f, 1.0f, 0.0f);     // Green
    glVertex3f(width / 2, length / 2, -depth / 2);
    glVertex3f(-width / 2, length / 2, -depth / 2);
    glVertex3f(-width / 2, length / 2, depth / 2);
    glVertex3f(width / 2, length / 2, depth / 2);

    // Bottom face (y = -1.0f)
    glColor3f(1.0f, 0.5f, 0.0f);     // Orange
    glVertex3f(width / 2, -length / 2, depth / 2);
    glVertex3f(-width / 2, -length / 2, depth / 2);
    glVertex3f(-width / 2, -length / 2, -depth / 2);
    glVertex3f(width / 2, -length / 2, -depth / 2);

    // Front face  (z = 1.0f)
    glColor3f(1.0f, 0.0f, 0.0f);     // Red
    glVertex3f(width / 2, length / 2, depth / 2);
    glVertex3f(-width / 2, length / 2, depth / 2);
    glVertex3f(-width / 2, -length / 2, depth / 2);
    glVertex3f(width / 2, -length / 2, depth / 2);

    // Back face (z = -1.0f)
    glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
    glVertex3f(width / 2, -length / 2, -depth / 2);
    glVertex3f(-width / 2, -length / 2, -depth / 2);
    glVertex3f(-width / 2, length / 2, -depth / 2);
    glVertex3f(width / 2, length / 2, -depth / 2);

    // Left face (x = -1.0f)
    glColor3f(0.0f, 0.0f, 1.0f);     // Blue
    glVertex3f(-width / 2, length / 2, depth / 2);
    glVertex3f(-width / 2, length / 2, -depth / 2);
    glVertex3f(-width / 2, -length / 2, -depth / 2);
    glVertex3f(-width / 2, -length / 2, depth / 2);

    // Right face (x = 1.0f)
    glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
    glVertex3f(width / 2, length / 2, -depth / 2);
    glVertex3f(width / 2, length / 2, depth / 2);
    glVertex3f(width / 2, -length / 2, depth / 2);
    glVertex3f(width / 2, -length / 2, -depth / 2);
    glEnd();
}
