#include <SDL3/SDL.h>
#include <cmath>
#include <iostream>
#include <vector>

#include "colors.h"
#include "light.h"
#include "sphere.h"
#include "math/vector.h"
#include "sdl_extentions.h"

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
    {{0, -1, 3}, 1, Colors::red},
    {{2, 0, 4.0f}, 1, Colors::green},
    {{-2, 0, 4}, 1, Colors::blue},
    {{0, -5001, 0}, 5000, Colors::yellow}
};

std::vector lights{
    Light::Ambient(0.2f),
    Light::Point(0.6f, {2, 1, 0}),
    Light::Directional(0.2, {1, 4, 4})
};

Vector canvas_to_viewpoint(int x, int y) {
    float vx = (static_cast<float>(x) - canvas.w / 2.0f) * (viewport.w / canvas.w);
    float vy = -(static_cast<float>(y) - canvas.h / 2.0f) * (viewport.h / canvas.h);
    const float vz = viewport.d;

    return Vector{vx, vy, vz};
}

float compute_lighting(const Vector &ray, const Vector &normal) {
    float intensity = 0;

    for (auto &light: lights) {
        if (light.type == LightType::Ambient) {
            intensity += light.intensity;
        } else {
            Vector direction = light.type == LightType::Point ? light.position - ray : light.direction;

            if (float normal_dot_light = normal.dot(direction); normal_dot_light > 0) {
                intensity += light.intensity * normal_dot_light / (normal.length() * direction.length());
            }
        }
    }

    return intensity;
}

float intersect_ray_sphere(const Vector &origin, const Vector &ray, const Sphere &sphere) {
    float r = sphere.radius;
    Vector CO = origin - sphere.center;

    // Calculate discriminant in quadratic equation
    float a = ray.dot(ray);
    float b = 2 * CO.dot(ray);
    float c = CO.dot(CO) - r * r;

    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return INFINITY;
    }

    float t1 = (-b + std::sqrt(discriminant)) / (2 * a);
    float t2 = (-b - std::sqrt(discriminant)) / (2 * a);

    return std::min(t1, t2);
}

SDL_Color trace_ray(const Vector &origin, const Vector &ray, float t_min) {
    float closest_t = INFINITY;
    const Sphere *closest_sphere = nullptr;

    for (auto &sphere: spheres) {
        auto t = intersect_ray_sphere(origin, ray, sphere);

        if (t > t_min && t < closest_t) {
            closest_t = t;
            closest_sphere = &sphere;
        }
    }

    if (closest_sphere == nullptr) {
        return Colors::white;
    }

    Vector intersection = origin + ray * closest_t;
    Vector normal = (intersection - closest_sphere->center).normalized();

    return closest_sphere->color * compute_lighting(intersection, normal);
}

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

    Uint32 lastTime = SDL_GetTicks();
    int frameCount = 0;

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

        frameCount++;
        if (Uint32 currentTime = SDL_GetTicks(); currentTime - lastTime >= 1000) {
            float fps = static_cast<float>(frameCount) * 1000.0f / static_cast<float>(currentTime - lastTime);
            SDL_Log("FPS: %.2f", fps);
            frameCount = 0;
            lastTime = currentTime;
        }
    }

    SDL_Quit();

    return 0;
}
