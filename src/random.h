#ifndef RANDOM_H
#define RANDOM_H

#include <random>

class Random
{
public:
    int getRandom(int min, int max);

private:
    std::random_device engine;
};

#endif // RANDOM_H
