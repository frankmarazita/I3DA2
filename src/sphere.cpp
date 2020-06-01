#include "sphere.h"

Sphere::Sphere(float r, int stacks, int slices)
{
    this->stacks = stacks;
    this->slices = slices;

    this->r = r;

}

void Sphere::draw()
{
    float theta, phi;
    float x1, y1, z1, x2, y2, z2, x3, y3, z3, x4, y4, z4;
    float step_theta = 2.0 * M_PI / slices, step_phi = M_PI / stacks;

   // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    //  glBegin(GL_QUAD_STRIP) - mistake to put it here! Why?
    for (int j = 0; j <= stacks; j++) {
        phi = j / (float)stacks * M_PI;
        glBegin(GL_QUAD_STRIP);
        for (int i = 0; i <= slices; i++) {
            theta = i / (float)slices * 2.0 * M_PI;
            x1 = r * sinf(phi) * cosf(theta);
            y1 = r * sinf(phi) * sinf(theta);
            z1 = r * cosf(phi);
            x2 = r * sinf(phi + step_phi) * cosf(theta);
            y2 = r * sinf(phi + step_phi) * sinf(theta);
            z2 = r * cosf(phi + step_phi);
            glNormal3f(x1, y1, z1);
            glVertex3f(x1, y1, z1);
            glNormal3f(x2, y2, z2);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
    /*int i;
    glBegin(GL_POLYGON);
    for (i = 0; i < nv; i++)
        glVertex3fv((float*)& vertices[i]);
    glEnd();*/
}