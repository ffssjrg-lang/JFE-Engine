#include "character/JFECharacter.hpp"
#include <iostream>

int main() {
    JFECharacter c;

    if (!jfe_load_character(
        "assets/characters/KOF-Rugal/KOF-Rugal.def", &c)) {
        std::cout << "LOAD FAILED\n";
        return 1;
    }

    for (const auto& s : c.states) {
        if (s.number != 0) continue;

        std::cout << "STATE 0 CONTROLLERS\n";

        for (const auto& ctrl : s.controllers) {
            std::cout << "\nTYPE: " << ctrl.type << "\n";

            for (const auto& p : ctrl.parameters)
                std::cout << "PARAM: " << p << "\n";

            for (const auto& t : ctrl.triggers)
                std::cout << "TRIGGER: " << t << "\n";
        }
    }
}
