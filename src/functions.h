#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#ifndef M_PI
#define M_PI 3.141592653589793238463
#endif

#include "vec2f.h"
#include "vec2fPolar.h"
#include "vec3f.h"

#include <cmath>

float radToDeg(float rad);
float degToRad(float deg);
float gradToRad(float grad);
float calcGrad(float x1, float y1, float x2, float y2);
vec2f polarToCartesian(vec2fPolar polar);
vec2fPolar cartesianToPolar(vec2f cart);
float calcVectorDistance(vec3f v1, vec3f v2);

#endif // FUNCTIONS_H