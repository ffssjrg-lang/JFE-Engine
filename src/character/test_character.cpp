#include "character/JFECharacter.hpp"

#include <iostream>
#include <string>
#include <map>

int main() {
    JFECharacter rugal;

    const char* def =
        "assets/characters/KOF-Rugal/KOF-Rugal.def";

    if (!jfe_load_character(def, &rugal)) {
        std::cout << "JFE CHARACTER LOAD FAILED\n";
        return 1;
    }

    size_t totalControllers = 0;
    size_t totalTriggers = 0;
    size_t totalTriggerAll = 0;

    std::map<std::string, size_t> controllerTypes;

    for (const auto& state : rugal.states) {
        totalControllers += state.controllers.size();

        for (const auto& controller : state.controllers) {
            totalTriggers += controller.triggers.size();
            totalTriggerAll += controller.triggerAll.size();

            if (!controller.type.empty()) {
                controllerTypes[controller.type]++;
            }
        }
    }

    std::cout << "===== JFE CHARACTER =====\n";
    std::cout << "Name: " << rugal.def.name << "\n";
    std::cout << "Sprites: " << rugal.sprites.size() << "\n";
    std::cout << "Animations: " << rugal.animations.size() << "\n";
    std::cout << "Commands: " << rugal.commands.size() << "\n";
    std::cout << "CNS Values: " << rugal.cnsValues.size() << "\n";
    std::cout << "States: " << rugal.states.size() << "\n";
    std::cout << "Controllers: " << totalControllers << "\n";
    std::cout << "Triggers: " << totalTriggers << "\n";
    std::cout << "TriggerAll: " << totalTriggerAll << "\n";

    std::cout << "\n===== CONTROLLER TYPES =====\n";

    for (const auto& item : controllerTypes) {
        std::cout << item.first << ": "
                  << item.second << "\n";
    }

    std::cout << "\nPalette Colors: "
              << rugal.palette.size() << "\n";

    std::cout << "Loaded: " << rugal.loaded << "\n";
    std::cout << "JFE CONTROLLER ANALYSIS SUCCESS\n";

    return 0;
}
