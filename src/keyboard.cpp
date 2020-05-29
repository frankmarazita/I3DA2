#include "keyboard.h"

Keyboard::Keyboard()
{
}

void Keyboard::keyDown(unsigned char key)
{
    pressed.push_back(key);
}

void Keyboard::keyDownSpecial(int key)
{
    pressedSpecial.push_back(key);
}

void Keyboard::keyUp(unsigned char key)
{
    // When a key is released, remove from list
    for (std::list<unsigned char>::iterator i = pressed.begin();
         i != pressed.end(); ++i)
        if (*i == key)
        {
            pressed.erase(i);
            break;
        }
}

void Keyboard::keyUpSpecial(int key)
{
    // When a key is released, remove from list
    for (std::list<int>::iterator i = pressedSpecial.begin();
        i != pressedSpecial.end(); ++i)
        if (*i == key)
        {
            pressedSpecial.erase(i);
            break;
        }
}

std::list<unsigned char> *Keyboard::getPressed()
{
    return &pressed;
}

std::list<int>* Keyboard::getPressedSpecial()
{
    return &pressedSpecial;
}