#include "character/JFECharacter.hpp"
#include "character/StateRuntime.hpp"
#include <iostream>

int main() {
    JFECharacter character;
    JFEStateRuntime runtime;

    if (!jfe_load_character(
        "assets/characters/KOF-Rugal/KOF-Rugal.def",
        &character)) {
        std::cout << "CHARACTER LOAD FAILED\n";
        return 1;
    }

    std::cout << "Character: " << character.def.name << "\n";
    std::cout << "Sprites: " << character.sprites.size() << "\n";
    std::cout << "Animations: " << character.animations.size() << "\n";
    std::cout << "States: " << character.states.size() << "\n";

    if (!jfe_state_runtime_enter(&character, &runtime, 0)) {
        std::cout << "STATE ENTRY FAILED\n";
        return 1;
    }

    std::cout << "Before ChangeAnim: "
              << runtime.animation << "\n";

    int changed = jfe_state_runtime_apply_change_anim(
        &character, &runtime
    );

    std::cout << "ChangeAnim Result: " << changed << "\n";
    std::cout << "Current State: " << runtime.currentState << "\n";
    std::cout << "Animation: " << runtime.animation << "\n";

    std::cout << "AnimTime: "
              << jfe_state_runtime_anim_time(&character, &runtime)
              << "\n";

    return runtime.animation == 0 ? 0 : 1;
}
