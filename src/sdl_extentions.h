#ifndef SDL_EXTENTIONS_H
#define SDL_EXTENTIONS_H

#include <algorithm>
#include <SDL3/SDL_pixels.h>

inline SDL_Color operator*(float m, const SDL_Color &color) {
    return {
        static_cast<Uint8>(std::clamp(static_cast<int>(static_cast<float>(color.r) * m), 0, 255)),
        static_cast<Uint8>(std::clamp(static_cast<int>(static_cast<float>(color.g) * m), 0, 255)),
        static_cast<Uint8>(std::clamp(static_cast<int>(static_cast<float>(color.b) * m), 0, 255)),
        color.a
    };
}

inline SDL_Color operator*(const SDL_Color &color, float m) {
    return {
        static_cast<Uint8>(std::clamp(static_cast<int>(static_cast<float>(color.r) * m), 0, 255)),
        static_cast<Uint8>(std::clamp(static_cast<int>(static_cast<float>(color.g) * m), 0, 255)),
        static_cast<Uint8>(std::clamp(static_cast<int>(static_cast<float>(color.b) * m), 0, 255)),
        color.a
    };
}

#endif //SDL_EXTENTIONS_H
