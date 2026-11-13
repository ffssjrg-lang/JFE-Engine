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

    std::cout << "===== JFE STATE RUNTIME TEST =====\n";

    int tests[] = {190, 195, 200};

    for (int number : tests) {
        if (jfe_state_runtime_enter(
            &rugal, &runtime, number
        )) {
            std::cout
                << "State: " << runtime.currentState
                << " | Anim: " << runtime.animation
                << " | Ctrl: " << runtime.control
                << " | Type: " << runtime.stateType
                << " | MoveType: " << runtime.moveType
                << "\n";

            jfe_state_runtime_tick(&runtime);

            std::cout
                << "State Time: "
                << runtime.stateTime << "\n";
        }
        else {
            std::cout
                << "State " << number << " NOT FOUND\n";
        }
    }

    std::cout << "JFE STATE RUNTIME TEST FINISHED\n";
    return 0;
}
