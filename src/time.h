#ifndef TIME_H
#define TIME_H

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