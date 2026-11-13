#include <SDL.h>
#include <cstdio>
#include <unordered_map>
#include <cstdint>

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static std::unordered_map<int, SDL_Texture*> spriteTextures;
static bool touching = false;
static float touchX = 0.0f;
static float touchY = 0.0f;

static bool leftPressed = false;
static bool rightPressed = false;
static bool attackPressed = false;

extern "C" {

int jfe_graphics_init() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        printf("SDL Error: %s\n", SDL_GetError());
        return 0;
    }
    return 1;
}

int jfe_create_window(int width, int height) {
    window = SDL_CreateWindow(
        "JFE - Jobayer Fighting Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width, height,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        printf("Window Error: %s\n", SDL_GetError());
        return 0;
    }

    renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED
    );

    if (!renderer) {
        printf("Renderer Error: %s\n", SDL_GetError());
        return 0;
    }

    return 1;
}

int jfe_poll_events() {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return 0;

        if (event.type == SDL_KEYDOWN) {
            if (event.key.keysym.sym == SDLK_LEFT)
                leftPressed = true;

            if (event.key.keysym.sym == SDLK_RIGHT)
                rightPressed = true;

            if (event.key.keysym.sym == SDLK_SPACE)
                attackPressed = true;
        }

        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_LEFT)
                leftPressed = false;

            if (event.key.keysym.sym == SDLK_RIGHT)
                rightPressed = false;

            if (event.key.keysym.sym == SDLK_SPACE)
                attackPressed = false;
        }

        if (event.type == SDL_FINGERDOWN ||
            event.type == SDL_FINGERMOTION) {
            touching = true;
            touchX = event.tfinger.x;
            touchY = event.tfinger.y;
        }

        if (event.type == SDL_FINGERUP) {
            touching = false;
            touchX = 0.0f;
            touchY = 0.0f;
        }
    }

    return 1;
}

int jfe_is_touching() {
    return touching ? 1 : 0;
}

float jfe_touch_x() {
    return touchX;
}

float jfe_touch_y() {
    return touchY;
}

int jfe_is_left_pressed() {
    return leftPressed ? 1 : 0;
}

int jfe_is_right_pressed() {
    return rightPressed ? 1 : 0;
}

int jfe_is_attack_pressed() {
    return attackPressed ? 1 : 0;
}

void jfe_clear_screen() {
    if (!renderer) return;

    SDL_SetRenderDrawColor(renderer, 20, 20, 35, 255);
    SDL_RenderClear(renderer);
}

void jfe_present() {
    if (renderer)
        SDL_RenderPresent(renderer);
}

void jfe_graphics_shutdown() {
    for (auto& item : spriteTextures) {
        if (item.second)
            SDL_DestroyTexture(item.second);
    }

    spriteTextures.clear();

    if (renderer) SDL_DestroyRenderer(renderer);
    if (window) SDL_DestroyWindow(window);

    renderer = nullptr;
    window = nullptr;

    SDL_Quit();
}


void jfe_draw_rect(int x, int y, int w, int h,
                   int r, int g, int b, int a) {
    if (!renderer) return;

    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    SDL_Rect rect = {x, y, w, h};
    SDL_RenderFillRect(renderer, &rect);
}

void jfe_draw_line(int x1, int y1, int x2, int y2,
                   int r, int g, int b, int a) {
    if (!renderer) return;

    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

}

void jfe_draw_rgba_sprite(
    int spriteId,
    const unsigned char* pixels,
    int width,
    int height,
    int x,
    int y,
    int drawWidth,
    int drawHeight
) {
    if (!renderer || !pixels || width <= 0 || height <= 0)
        return;

    SDL_Texture* texture = nullptr;

    auto it = spriteTextures.find(spriteId);

    if (it == spriteTextures.end()) {
        texture = SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_RGBA32,
            SDL_TEXTUREACCESS_STATIC,
            width,
            height
        );

        if (!texture)
            return;

        SDL_UpdateTexture(
            texture, nullptr, pixels, width * 4
        );

        SDL_SetTextureBlendMode(
            texture, SDL_BLENDMODE_BLEND
        );

        spriteTextures[spriteId] = texture;
    } else {
        texture = it->second;
    }

    SDL_Rect destination = {
        x, y, drawWidth, drawHeight
    };

    SDL_RenderCopy(renderer, texture, nullptr, &destination);
}

