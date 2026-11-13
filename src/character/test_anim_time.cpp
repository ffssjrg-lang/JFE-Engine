#include "character/JFECharacter.hpp"
#include "character/StateRuntime.hpp"

#include <iostream>

int main() {
    JFECharacter rugal;
    JFEStateRuntime runtime;

    if (!jfe_load_character(
        "assets/characters/KOF-Rugal/KOF-Rugal.def",
        &rugal
    )) {
        std::cout << "CHARACTER LOAD FAILED\n";
        return 1;
    }

    if (!jfe_state_runtime_enter(&rugal, &runtime, 190)) {
        std::cout << "STATE 190 NOT FOUND\n";
        return 1;
    }

    if (!jfe_state_runtime_start_animation(&rugal, &runtime)) {
        std::cout << "ANIMATION 190 NOT FOUND\n";
        return 1;
    }

    std::cout << "Initial AnimTime: "
              << jfe_state_runtime_anim_time(&rugal, &runtime)
              << "\n";

    jfe_state_runtime_tick_animation(&rugal, &runtime);

    std::cout << "After 1 Tick: "
              << jfe_state_runtime_anim_time(&rugal, &runtime)
              << "\n";

    for (int i = 1; i < 150; i++) {
        jfe_state_runtime_tick_animation(&rugal, &runtime);
    }

    std::cout << "After 150 Ticks: "
              << jfe_state_runtime_anim_time(&rugal, &runtime)
              << "\n";

    std::cout << "Animation Finished: "
              << runtime.animationFinished << "\n";

    return 0;
}
