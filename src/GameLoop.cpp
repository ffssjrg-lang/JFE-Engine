#include <SDL.h>

extern "C" {
int jfe_poll_events();
void jfe_clear_screen();
void jfe_present();

void jfe_update_fight_scene();
void jfe_render_fight_scene();

static bool running = false;

void jfe_run_game_loop() {
    running = true;

    while (running) {
        if (!jfe_poll_events()) {
            running = false;
            break;
        }

        jfe_update_fight_scene();

        jfe_clear_screen();
        jfe_render_fight_scene();
        jfe_present();

        SDL_Delay(16);
    }
}

void jfe_stop_game_loop() {
    running = false;
}
}
