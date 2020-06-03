#ifndef TIME_H
#define TIME_H

#include "vec2f.h"
#include "vec2fPolar.h"
#include "vec3f.h"
#include "functions.h"
#include "3d_wave.h"

#include <cmath>
#include <list>

#include "opengl.h"
#include "texture.h"

class Time
{
public:
    Time();
    void resume();
    void pause();
    void toggle();
    void update(int time);
    int getTime();

    int pausedTime;
    int glutTime;
    bool paused;
private:
    int offset;
};

#endif // TIME_H