#include "3d_wave.h"

Wave3D::Wave3D(float windowSize, float numSegments, float a, float b, float k, float c, float d)
{
    this->windowSize = windowSize;
    this->numSegments = numSegments;
    this->segmentSize = windowSize * 2 / numSegments;

    this->a = a;
    this->b = b;
    this->k = k;
    this->c = c;
    this->d = d;

    calcVerticies();
}

float Wave3D::getYfromXZ(float x, float z)
{
    return a * sinf(b * x + k * c) + a * sinf(b * z + k * c) + d;
}

vec3f Wave3D::getGradientForAdvancedSine(float x, float z)
{
    float vx = a * b * cosf(b * x + k * c);
    float vz = a * b * cosf(b * z + k * c);

    return {vx, 1, vz};
}

void Wave3D::drawAdvanced()
{
    float x = -windowSize;
    float z = windowSize;

    setLighting();
    glColor4f(col.r, col.g, col.b, col.a);

    glBegin(GL_TRIANGLE_STRIP);

    auto getXYZ = [&](int i, int j) {
        float px = x + j * segmentSize;
        float pz = z - i * segmentSize;
        float y = getYfromXZ(px, pz);

        vec3f vec = {px, y, pz};
        return vec;
    };

    auto drawVerticies = [&](int i, int j) {
        vec3f vec = getXYZ(i, j);

        float px = vec.x;
        float y = vec.y;
        float pz = vec.z;

        glNormal3f(px, y, pz);
        glVertex3f(px, y, pz);

        pz = windowSize - i * segmentSize - segmentSize;
        y = getYfromXZ(px, pz);

        glNormal3f(px, y, pz);
        glVertex3f(px, y, pz);
    };

    auto drawVectorsAndOrNormals = [&](int i, int j) {
        vec3f vec = getXYZ(i, j);
        float length = 0.03;

        if (normal)
        {
            vec3f mv = getGradientForAdvancedSine(vec.x, vec.z);
            drawVector(vec, mv, length, true);
        }
        if (tangent)
        {
            vec3f mv = getGradientForAdvancedSine(vec.x, vec.z);
            drawVector(vec, mv, length, false);
        }
    };

    auto drawFromMemory = [&](vec3f vec1, vec3f vec2) {
        vec1.y = getYfromXZ(vec1.x, vec1.z);
        vec2.y = getYfromXZ(vec2.x, vec2.z);
        glNormal3f(vec1.x, vec1.y, vec1.z);
        glVertex3f(vec1.x, vec1.y, vec1.z);
        glNormal3f(vec2.x, vec2.y, vec2.z);
        glVertex3f(vec2.x, vec2.y, vec2.z);
    };

    for (int i = 0; i < numSegments; i++)
    {
        if (i % 2 == 0)
        {
            for (int j = 0; j <= numSegments; j++)
            {
                vec3f vec1 = verticies[i * (numSegments + 1) + j];
                vec3f vec2 = verticies[(i + 1) * (numSegments + 1) + j];
                drawFromMemory(vec1, vec2);
            }
        }
        else
        {
            for (int j = numSegments; j >= 0; j--)
            {
                vec3f vec1 = verticies[i * (numSegments + 1) + j];
                vec3f vec2 = verticies[(i + 1) * (numSegments + 1) + j];
                drawFromMemory(vec1, vec2);
            }
        }
    }
    glEnd();

    disableLighting();

    if (tangent || normal)
    {
        for (int i = 0; i <= numSegments; i++)
        {
            if (i % 2 == 0)
            {
                for (int j = 0; j <= numSegments; j++)
                    drawVectorsAndOrNormals(i, j);
            }
            else
            {
                for (int j = numSegments; j >= 0; j--)
                    drawVectorsAndOrNormals(i, j);
            }
        }
    }
}

void Wave3D::setLighting()
{
    glBlendFunc(GL_ONE, GL_ONE); // Enables Transparency

    glEnable(GL_LIGHT1);
    GLfloat light_ambient[] = {0.2, 0.5, 1.0, 0.75};
    GLfloat light_diffuse[] = {0.2, 0.5, 1.0, 0.75};
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    GLfloat mat_specular[] = {0.2, 0.5, 1.0, 0};
    GLfloat high_shininess[] = {100.0};
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position);
    // glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    // glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, high_shininess);
}

void Wave3D::disableLighting()
{
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glDisable(GL_LIGHTING);
    glDisable(GL_LIGHT1);
}

void Wave3D::moveWave(float amount)
{
    // Set the wave displacement c value
    c = amount;
}

void Wave3D::calcVerticies()
{
    // Calculate the initial verticies locations based on num segments
    verticies.clear();
    verticies.reserve((numSegments + 1) ^ 2);
    for (int i = 0; i <= numSegments; i++)
    {
        for (int j = 0; j <= numSegments; j++)
        {
            float z = windowSize - segmentSize * i;
            float x = -windowSize + segmentSize * j;
            verticies.push_back({x, 0, z});
        }
    }
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

void Wave3D::drawVector(vec3f point, vec3f m, float s, bool normalize)
{
    vec3f endpoint = {0, 0, point.z};

    float mx = m.x;
    float mz = m.z;

    if (normalize)
    {
        glColor3f(0.0, 1.0, 0.0);
        mx = -(1 / m.x);
    }
    else
    {
        glColor3f(1.0, 0.0, 0.0);
    }

    if (mx < 0)
    {
        endpoint.x = point.x - cos(atan(mx)) * s;
        endpoint.y = point.y - sin(atan(mx)) * s;
        endpoint = rotatePointX(point, endpoint, atan(mz));
    }
    else
    {
        endpoint.x = point.x + cos(atan(mx)) * s;
        endpoint.y = point.y + sin(atan(mx)) * s;
        endpoint = rotatePointX(point, endpoint, atan(mz));
    }

    glBegin(GL_LINE_STRIP);
    glVertex3f(point.x, point.y, point.z);
    glVertex3f(endpoint.x, endpoint.y, endpoint.z);
    glEnd();
}