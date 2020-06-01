#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#ifndef M_PI
#define M_PI 3.141592653589793238463
#endif

#include "vec2f.h"
#include "vec2fPolar.h"
#include "vec3f.h"
#include "vec3fSpherical.h"

#include <cmath>

float radToDeg(float rad);
float radToGrad(float rad);
float degToRad(float deg);
float gradToRad(float grad);
float gradToDeg(float grad);
float calcGrad(float x1, float y1, float x2, float y2);
vec2f polarToCartesian(vec2fPolar polar);
vec2fPolar cartesianToPolar(vec2f cart);
float calcVectorDistance(vec3f v1, vec3f v2);
float calcVectorGrad(vec3f v1, vec3f v2);
vec3f rotatePointZ(vec3f pivotPoint, vec3f rotatePoint, float angleRad);
vec3f rotatePointY(vec3f pivotPoint, vec3f rotatePoint, float angleRad);
vec3f rotatePointX(vec3f pivotPoint, vec3f rotatePoint, float angleRad);
vec3f sphericalToCartesian(vec3fSpherical spherical);

#endif // FUNCTIONS_H