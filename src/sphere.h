#ifndef SPHERE_H
#define SPHERE_H

#include <SDL3/SDL_pixels.h>

#include "math/vector.h"

inline struct {
    Vector center;
    SDL_Color color{};
    float radius{};
} Sphere;

#endif //SPHERE_H
