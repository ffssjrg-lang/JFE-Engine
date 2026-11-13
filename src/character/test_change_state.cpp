#include "character/JFECharacter.hpp"
#include "character/StateRuntime.hpp"

#include <iostream>

int main() {
    JFECharacter rugal;
    JFEChangeStateInfo info;

    if (!jfe_load_character(
        "assets/characters/KOF-Rugal/KOF-Rugal.def",
        &rugal
    )) {
        std::cout << "CHARACTER LOAD FAILED\n";
        return 1;
    }

    if (jfe_state_runtime_find_change_state(
        &rugal, 190, &info
    )) {
        std::cout << "Controller: ChangeState\n";
        std::cout << "Target State: "
                  << info.targetState << "\n";
        std::cout << "Trigger: "
                  << info.trigger << "\n";
        std::cout << "JFE CHANGESTATE TEST SUCCESS\n";
    } else {
        std::cout << "CHANGESTATE NOT FOUND\n";
        return 1;
    }

    return 0;
}
