#ifndef THREE_D_ISLAND_H
#define THREE_D_ISLAND_H

#include "vec2f.h"
#include "vec2fPolar.h"
#include "vec3f.h"
#include "functions.h"
#include "3d_wave.h"

#include <cmath>
#include <list>
#include <string>

#include "opengl.h"
#include "texture.h"

class Island3D
{
public:
    Island3D();
    void draw();
    void drawHealth();
    void drawScore();

    bool collision(vec3f otherLocation, float otherRadius);

private:
    Texture *texture;
    GLUquadric *qobj;

    float radius = 0.25;
    int health = 100;
    int score = 0;

    vec3f location = {0, -0.5, 0};
};

#endif // THREE_D_ISLAND_H