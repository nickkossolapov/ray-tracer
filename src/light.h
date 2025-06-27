#ifndef LIGHT_H
#define LIGHT_H
#include "math/vector.h"

enum class LightType {
    Ambient,
    Point,
    Directional
};

struct Light {
    LightType type;
    float intensity;
    Vector position; // Used only for point lights
    Vector direction; // Used only for directional lights

    static Light Ambient(float intensity) {
        return Light{LightType::Ambient, intensity, Vector{0, 0, 0}, Vector{0, 0, 0}};
    }

    static Light Point(float intensity, const Vector &position) {
        return Light{LightType::Point, intensity, position, Vector{0, 0, 0}};
    }

    static Light Directional(float intensity, const Vector &direction) {
        return Light{LightType::Directional, intensity, Vector{0, 0, 0}, direction};
    }
};

#endif //LIGHT_H
