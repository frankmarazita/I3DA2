#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <list>
#include <iostream>

#include "opengl.h"

class Keyboard
{
public:
    Keyboard();

    void keyDown(unsigned char key);
    void keyUp(unsigned char key);

    void keyDownSpecial(int key);
    void keyUpSpecial(int key);

    std::list<unsigned char> *getPressed();
    std::list<int>* getPressedSpecial();
private:
    std::list<unsigned char> pressed;
    std::list<int> pressedSpecial;
};

#endif // KEYBOARD_H