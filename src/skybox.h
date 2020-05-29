#ifndef SKYBOX
#define SKYBOX

#include "vec2f.h"
#include "vec2fPolar.h"
#include "vec3f.h"

#include <cmath>

#include "opengl.h"
#include "texture.h"

class Skybox
{
public:
    Skybox();
    void draw();

private:
    Texture *textureTop;
    Texture *textureBack;
    Texture *textureFront;
    Texture *textureLeft;
    Texture *textureRight;

    GLUquadric *qobj;

    vec3f location = {0, 0, 0};
    float scale = 1;
};

#endif // SKYBOX