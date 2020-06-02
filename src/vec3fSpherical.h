#ifndef VEC3FSPHERICAL_H
#define VEC3FSPHERICAL_H

typedef struct
{
    float magnitude; // or radius, r
    float a; // or azimuthal angle, wack looking symbol
    float polar; // polar angle, generally theta
} vec3fSpherical;

#endif // VEC3FSPHERICAL_H