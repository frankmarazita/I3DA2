#include "functions.h"

float radToDeg(float rad)
{
    return rad * 180.0 / M_PI;
}

float radToGrad(float rad)
{
    return tan(rad);
}

float degToRad(float deg)
{
    return deg * M_PI / 180.0;
}

float gradToRad(float grad)
{
    return atan(grad);
}

float gradToDeg(float grad)
{
    return atan(grad) * 180.0 / M_PI;
}

float calcGrad(float x1, float y1, float x2, float y2)
{
    return (y2 - y1) / (x2 - x1);
}

vec3f sphericalToCartesian(vec3fSpherical spherical)
{
    vec3f cart;
    
    /*cart.x = spherical.magnitude * sinf(degToRad(spherical.a)) * cosf(degToRad(spherical.polar));
    cart.y = spherical.magnitude * sinf(degToRad(spherical.a)) * sinf(degToRad(spherical.polar));
    cart.z = spherical.magnitude * cosf(degToRad(spherical.a));*/

    /*cart.x = cosf(degToRad(spherical.a)) * spherical.magnitude;
    cart.y = sinf(degToRad(spherical.a)) * spherical.magnitude;
    cart.z = 0.0;*/

    // 2D Code
    cart.x = cosf(degToRad(spherical.a)) * spherical.magnitude;
    cart.y = sinf(degToRad(spherical.a)) * spherical.magnitude;
    cart.z = 0.0;
    return cart;
}

vec2f polarToCartesian(vec2fPolar polar)
{
    vec2f cart;
    cart.x = cos(degToRad(polar.angle)) * polar.magnitude;
    cart.y = sin(degToRad(polar.angle)) * polar.magnitude;
    return cart;
}

vec2fPolar cartesianToPolar(vec2f cart)
{
    vec2fPolar polar;
    polar.magnitude = sqrt(pow(cart.x, 2) + pow(cart.y, 2));
    polar.angle = radToDeg(gradToRad(cart.y / cart.x));
    return polar;
}

float calcVectorDistance(vec3f v1, vec3f v2)
{
    vec3f vec = {-v1.x + v2.x, -v1.y + v2.y, -v1.z + v2.z};
    float distance = sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
    return distance;
}

float calcVectorGrad(vec3f v1, vec3f v2)
{
    float rise = v2.y - v1.y;

    float xDist = v2.x - v1.x;
    float zDist = v2.z - v1.z;

    float run = sqrt(pow(xDist, 2) + pow(zDist, 2));

    float m = rise / run;

    return m;
}

vec3f rotatePointZ(vec3f pivotPoint, vec3f rotatePoint, float angleRad)
{
    float s = sin(angleRad);
    float c = cos(angleRad);

    // translate point back to origin:
    rotatePoint.x -= pivotPoint.x;
    rotatePoint.y -= pivotPoint.y;

    // rotate point
    float xnew = rotatePoint.x * c - rotatePoint.y * s;
    float ynew = rotatePoint.x * s + rotatePoint.y * c;

    // translate point back:
    rotatePoint.x = xnew + pivotPoint.x;
    rotatePoint.y = ynew + pivotPoint.y;

    return rotatePoint;
}

vec3f rotatePointY(vec3f pivotPoint, vec3f rotatePoint, float angleRad)
{
    float s = sin(-angleRad);
    float c = cos(-angleRad);

    // translate point back to origin:
    rotatePoint.x -= pivotPoint.x;
    rotatePoint.z -= pivotPoint.z;

    // rotate point
    float xnew = rotatePoint.x * c - rotatePoint.z * s;
    float znew = rotatePoint.x * s + rotatePoint.z * c;

    // translate point back:
    rotatePoint.x = xnew + pivotPoint.x;
    rotatePoint.z = znew + pivotPoint.z;

    return rotatePoint;
}

vec3f rotatePointX(vec3f pivotPoint, vec3f rotatePoint, float angleRad)
{
    float s = sin(-angleRad);
    float c = cos(-angleRad);

    // translate point back to origin:
    rotatePoint.y -= pivotPoint.y;
    rotatePoint.z -= pivotPoint.z;

    // rotate point
    float ynew = rotatePoint.y * c - rotatePoint.z * s;
    float znew = rotatePoint.y * s + rotatePoint.z * c;

    // translate point back:
    rotatePoint.y = ynew + pivotPoint.y;
    rotatePoint.z = znew + pivotPoint.z;

    return rotatePoint;
}