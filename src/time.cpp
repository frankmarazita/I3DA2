#include "time.h"

Time::Time()
{
    this->offset = 0;
    this->glutTime = 0;
    this->paused = false;
    this->pausedTime = 0;
}

void Time::toggle()
{
    if (!this->paused)
        this->pause();
    else
        this->resume();
}

void Time::resume()
{
    if (!this->paused)
        return;

    this->offset = this->offset + (this->glutTime - this->pausedTime);
    this->pausedTime = 0;
    this->paused = false;
}

int Time::getTime()
{
    if (this->paused)
        return this->pausedTime - this->offset;

    return this->glutTime - this->offset;
}

void Time::pause()
{
    if (this->paused)
        return;

    this->pausedTime = this->glutTime;
    this->paused = true;
}

void Time::update(int time)
{
    this->glutTime = time;
}