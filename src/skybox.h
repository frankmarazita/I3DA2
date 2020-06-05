#ifndef SKYBOX
#define SKYBOX

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

    float scale = 1;
};

#endif // SKYBOX