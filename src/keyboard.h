#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <list>
#include <iostream>

#if _WIN32
#   include <Windows.h>
#endif
#if __APPLE__
#   include <OpenGL/gl.h>
#   include <OpenGL/glu.h>
#   include <GLUT/glut.h>
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#   include <GL/glut.h>
#endif

class Keyboard
{
public:
    Keyboard();

    void keyDown(unsigned char key);
    void keyUp(unsigned char key);

    std::list<unsigned char> *getPressed();

private:
    std::list<unsigned char> pressed;
};

#endif // KEYBOARD_H