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
        std::cout << "ANIMATION START FAILED\n";
        return 1;
    }

    std::cout << "Starting State: "
              << runtime.currentState << "\n";

    for (int i = 0; i < 150; i++) {
        jfe_state_runtime_tick_animation(&rugal, &runtime);

        if (jfe_state_runtime_apply_change_state(&rugal, &runtime)) {
            std::cout << "CHANGE STATE SUCCESS\n";
            break;
        }
    }

    std::cout << "Final State: "
              << runtime.currentState << "\n";

    std::cout << "Previous State: "
              << runtime.previousState << "\n";

    std::cout << "State Time: "
              << runtime.stateTime << "\n";

    return 0;
}
