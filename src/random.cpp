#include "random.h"

int Random::getRandom(int min, int max)
{
    // Returns values with range [min, max]
    std::uniform_int_distribution<int> uniform_dist(min, max);

    int randomNumber = uniform_dist(engine);

    return randomNumber;
}