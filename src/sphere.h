#ifndef SPHERE_H
#define SPHERE_H

#include <SDL3/SDL_pixels.h>

#include "math/vector.h"

struct Sphere {
    Vector center;
    float radius;
    SDL_Color color;
};

#endif //SPHERE_H
