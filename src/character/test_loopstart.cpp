#include "character/JFECharacter.hpp"
#include "character/StateRuntime.hpp"
#include <iostream>

int main() {
    JFECharacter character;

    if (!jfe_load_character(
        "assets/characters/KOF-Rugal/KOF-Rugal.def",
        &character)) {
        std::cout << "LOAD FAILED\n";
        return 1;
    }

    for (const auto& action : character.animations) {
        if (!action.loopStart ||
            action.loopStartFrameIndex < 0 ||
            action.loopStartFrameIndex >=
                static_cast<int>(action.frames.size())) {
            continue;
        }

        JFEStateRuntime runtime;
        runtime.active = true;
        runtime.animation = action.number;
        runtime.animationFrameIndex =
            static_cast<int>(action.frames.size()) - 1;
        runtime.animationFrameTime =
            action.frames.back().duration > 0
            ? action.frames.back().duration - 1 : 0;

        std::cout << "Action: " << action.number << "\n";
        std::cout << "Frames: " << action.frames.size() << "\n";
        std::cout << "Expected Loop Frame: "
                  << action.loopStartFrameIndex << "\n";

        jfe_state_runtime_tick_animation(&character, &runtime);

        std::cout << "Actual Loop Frame: "
                  << runtime.animationFrameIndex << "\n";

        if (runtime.animationFrameIndex ==
            action.loopStartFrameIndex) {
            std::cout << "LOOPSTART TEST SUCCESS\n";
            return 0;
        }

        std::cout << "LOOPSTART TEST FAILED\n";
        return 1;
    }

    std::cout << "NO VALID LOOPSTART ACTION FOUND\n";
    return 2;
}
