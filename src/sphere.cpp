#include "sphere.h"

Sphere::Sphere(float r, int stacks, int slices)
{
    this->stacks = stacks;
    this->slices = slices;

    this->r = r;

    // Allocate arrays 
    this->vertices = (vec3f**)calloc(stacks + 1, sizeof(vec3f*));
    this->texes = (tex2f**)calloc(stacks + 1, sizeof(tex2f*));
    for (int stack = 0; stack <= stacks; stack++)
    {
        this->vertices[stack] = (vec3f*)calloc(slices + 1, sizeof(vec3f));
        this->texes[stack] = (tex2f*)calloc(slices + 1, sizeof(tex2f));
    }

    // Initialise arrays
    for (int stack = 0; stack <= stacks; stack++)
    {
        float theta = stack * M_PI / (float)stacks;
        for (int slice = 0; slice <= slices; slice++)
        {
            float phi = slice * 2 * M_PI / (float)slices;

            // Vertex coordinates
            vec3f v;
            v.x = r * sinf(theta) * cosf(phi);
            v.z = r * sinf(theta) * sinf(phi);
            v.y = r * cosf(theta);
            this->vertices[stack][slice] = v;

            // Texture coordinates
            tex2f tc;
            tc.u = 1 - (float)slice / (float)slices,
            tc.v = 1 - (float)stack / (float)stacks;
            this->texes[stack][slice] = tc;
        }
    }

}

Sphere::~Sphere()
{
    for (int stack = 0; stack <= stacks; stack++)
    {
        free(this->vertices[stack]);
        free(this->texes[stack]);
    }
    free(this->vertices);
    free(this->texes);
}

void Sphere::draw(bool showNormals)
{
    glBegin(GL_QUADS);
    for (int stack = 0; stack < this->stacks; stack++)
    {
        for (int slice = 0; slice < this->slices; slice++)
        {
            glTexCoord2fv((GLfloat*)& this->texes[stack][slice]);
            glNormal3fv((GLfloat*)& this->vertices[stack][slice]);
            glVertex3fv((GLfloat*)& this->vertices[stack][slice]);

            glTexCoord2fv((GLfloat*)& this->texes[stack + 1][slice]);
            glNormal3fv((GLfloat*)& this->vertices[stack + 1][slice]);
            glVertex3fv((GLfloat*)& this->vertices[stack + 1][slice]);

            glTexCoord2fv((GLfloat*)& this->texes[stack + 1][slice + 1]);
            glNormal3fv((GLfloat*)& this->vertices[stack + 1][slice + 1]);
            glVertex3fv((GLfloat*)& this->vertices[stack + 1][slice + 1]);

            glTexCoord2fv((GLfloat*)& this->texes[stack][slice + 1]);
            glNormal3fv((GLfloat*)& this->vertices[stack][slice + 1]);
            glVertex3fv((GLfloat*)& this->vertices[stack][slice + 1]);
        }
    }
    glEnd();
}