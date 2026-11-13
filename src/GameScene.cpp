#include "EngineCore.hpp"
#include "character/JFECharacter.hpp"
#include "character/StateRuntime.hpp"
#ifdef __ANDROID__
#include <SDL.h>
#include <string>
#endif

extern "C" {
void jfe_draw_rect(int, int, int, int, int, int, int, int);
void jfe_draw_fighter(int, int, int);
int jfe_draw_character_sprite(
    const JFECharacter*,
    const JFEStateRuntime*,
    int, int, int
);
void jfe_draw_health_bar(int, int, int, int);

int jfe_is_left_pressed();
int jfe_is_right_pressed();
int jfe_is_attack_pressed();
}

static JFEFighter player1;
static JFEFighter player2;

static JFECharacter rugal;

static JFEStateRuntime runtime1;
static JFEStateRuntime runtime2;

static bool initialized = false;
static bool characterLoaded = false;
static bool previousAttack = false;

extern "C" {

void jfe_scene_init() {
    jfe_init_fighter(&player1, 1.5f);
    jfe_init_fighter(&player2, 6.0f);

    previousAttack = false;

#ifdef __ANDROID__
    const char* internalPath = SDL_AndroidGetInternalStoragePath();
    std::string defPath = std::string(
        internalPath ? internalPath : ""
    ) + "/characters/KOF-Rugal/KOF-Rugal.def";
#else
    std::string defPath =
        "assets/characters/KOF-Rugal/KOF-Rugal.def";
#endif

    characterLoaded = jfe_load_character(
        defPath.c_str(),
        &rugal
    ) != 0;

    if (characterLoaded) {
        if (jfe_state_runtime_enter(&rugal, &runtime1, 0))
            jfe_state_runtime_start_animation(&rugal, &runtime1);

        if (jfe_state_runtime_enter(&rugal, &runtime2, 0))
            jfe_state_runtime_start_animation(&rugal, &runtime2);
    }

    initialized = true;
}

void jfe_update_fight_scene() {
    if (!initialized)
        jfe_scene_init();

    if (jfe_is_left_pressed())
        jfe_move(&player1, -0.04f);

    if (jfe_is_right_pressed())
        jfe_move(&player1, 0.04f);

    if (player1.x < 0.0f)
        player1.x = 0.0f;

    if (player1.x > 6.0f)
        player1.x = 6.0f;

    bool attack = jfe_is_attack_pressed();

    if (attack && !previousAttack)
        jfe_attack(&player1, &player2);

    previousAttack = attack;

    if (characterLoaded) {
        jfe_state_runtime_update(&rugal, &runtime1);
        jfe_state_runtime_update(&rugal, &runtime2);
    }
}

void jfe_render_fight_scene() {
    if (!initialized)
        jfe_scene_init();

    jfe_draw_rect(0, 370, 800, 80, 65, 55, 50, 255);

    jfe_draw_health_bar(30, 25, player1.health, 1);
    jfe_draw_health_bar(570, 25, player2.health, 2);

    if (!characterLoaded ||
        !jfe_draw_character_sprite(
            &rugal, &runtime1,
            (int)(player1.x * 100), 350, 1))
        jfe_draw_fighter((int)(player1.x * 100), 230, 1);

    if (!characterLoaded ||
        !jfe_draw_character_sprite(
            &rugal, &runtime2,
            (int)(player2.x * 100), 350, 1))
        jfe_draw_fighter((int)(player2.x * 100), 230, 2);
}

}
