#include <SDL.h>

extern "C" {
int jfe_graphics_init();
int jfe_create_window(int width, int height);
void jfe_run_game_loop();
void jfe_graphics_shutdown();
}

extern "C" int SDL_main(int argc, char** argv) {
    (void)argc;
    (void)argv;

    if (!jfe_graphics_init())
        return 1;

    if (!jfe_create_window(800, 450)) {
        jfe_graphics_shutdown();
        return 1;
    }

    jfe_run_game_loop();
    jfe_graphics_shutdown();

    return 0;
}
