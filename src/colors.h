#ifndef COLORS_H
#define COLORS_H

#include <SDL3/SDL_pixels.h>

namespace Colors {
    constexpr SDL_Color white = {0xF2, 0xF2, 0xF2};
    constexpr SDL_Color black = {0x22, 0x22, 0x22};
    constexpr SDL_Color grey = {0x30, 0x30, 0x30};

    constexpr SDL_Color red = {0xFF, 0x00, 0x00};
    constexpr SDL_Color green = {0x00, 0xFF, 0x00};
    constexpr SDL_Color blue = {0x00, 0x00, 0xFF};
}

#endif //COLORS_H
