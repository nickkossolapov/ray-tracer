#include <SDL3/SDL.h>
#include <cmath>
#include <iostream>
#include <vector>

#include "colors.h"
#include "sphere.h"
#include "math/vector.h"

static SDL_Window *window = nullptr;
static SDL_Renderer *renderer = nullptr;

struct {
    float w = 1000;
    float h = 1000;
} canvas;

struct {
    float w = 1;
    float h = 1;
    float d = 1;
} viewport;

std::vector<Sphere> spheres{
    {Vector{0.0f, -1.0f, 3.0f}, 1.0f, Colors::red},
    {Vector{2.0f, 0.0f, 4.0f}, 1.0f, Colors::green},
    {Vector{-2.0f, 0.0f, 4.0f}, 1.0f, Colors::blue}
};

Vector canvas_to_viewpoint(int x, int y) {
    float vx = (static_cast<float>(x) - canvas.w / 2.0f) * (viewport.w / canvas.w);
    float vy = -(static_cast<float>(y) - canvas.h / 2.0f) * (viewport.h / canvas.h);
    const float vz = viewport.d;

    return Vector{vx, vy, vz};
}


std::tuple<float, float> intersect_ray_sphere(const Vector &O, const Vector &D, const Sphere &sphere) {
    float r = sphere.radius;
    Vector CO = O - sphere.center;

    // Calculate discriminant in quadratic equation
    float a = D.dot(D);
    float b = 2 * CO.dot(D);
    float c = CO.dot(CO) - r * r;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return {INFINITY, INFINITY};
    }

    float t1 = (-b + std::sqrt(discriminant)) / (2 * a);
    float t2 = (-b - std::sqrt(discriminant)) / (2 * a);

    return {t1, t2};
};

SDL_Color trace_ray(const Vector &O, const Vector &D, float t_min) {
    float closest_t = INFINITY;
    const Sphere *closest_sphere = nullptr;

    for (auto &sphere: spheres) {
        auto [t1, t2] = intersect_ray_sphere(O, D, sphere);

        if (t1 > t_min && t1 < closest_t) {
            closest_t = t1;
            closest_sphere = &sphere;
        }

        if (t2 > t_min && t2 < closest_t) {
            closest_t = t2;
            closest_sphere = &sphere;
        }
    }

    if (closest_sphere == nullptr) {
        return Colors::white;
    }

    return closest_sphere->color;
};

void draw_point(int x, int y, SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderPoint(renderer, static_cast<float>(x), static_cast<float>(y));
}

void prepareRenderer() {
    auto [r, g, b, a] = Colors::white;
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderClear(renderer);
}

int main(int argc, char *argv[]) {
    bool quit = false;
    SDL_Event e;

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());

        exit(SDL_APP_FAILURE);
    }

    if (!SDL_CreateWindowAndRenderer("ray-tracer", static_cast<int>(canvas.w), static_cast<int>(canvas.h), 0, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());

        exit(SDL_APP_FAILURE);
    }

    Vector origin = {0.0f, 0.0f, 0.0f};

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_EVENT_QUIT || (e.type == SDL_EVENT_KEY_UP && e.key.key == SDLK_ESCAPE)) {
                quit = true;
            }
        }

        prepareRenderer();

        int y_end = static_cast<int>(canvas.h);
        int x_end = static_cast<int>(canvas.w);

        for (int y = 0; y < y_end; ++y) {
            for (int x = 0; x < x_end; ++x) {
                Vector D = canvas_to_viewpoint(x, y);
                SDL_Color color = trace_ray(origin, D, viewport.d);

                draw_point(x, y, color);
            }
        }

        SDL_RenderPresent(renderer);
    }

    SDL_Quit();

    return 0;
}
