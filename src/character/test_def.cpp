#include "character/CharacterDef.hpp"
#include <iostream>

int main() {
    JFECharacterDef c;

    const char* path =
        "assets/characters/KOF-Rugal/KOF-Rugal.def";

    if (!jfe_load_character_def(path, &c)) {
        std::cout << "DEF LOAD FAILED\n";
        return 1;
    }

    std::cout << "===== JFE RUGAL TEST =====\n";
    std::cout << "Name: " << c.name << "\n";
    std::cout << "Display Name: " << c.displayname << "\n";
    std::cout << "Author: " << c.author << "\n";
    std::cout << "MUGEN Version: " << c.mugenversion << "\n";
    std::cout << "Localcoord: " << c.localcoordX
              << " x " << c.localcoordY << "\n";

    std::cout << "\n===== CHARACTER FILES =====\n";
    for (const auto& f : c.files) {
        std::cout << f.key << " = " << f.path << "\n";
    }

    std::cout << "\nTotal Files: " << c.files.size() << "\n";
    std::cout << "Total Palettes: " << c.palettes.size() << "\n";
    std::cout << "\nJFE RUGAL DEF TEST SUCCESS\n";

    return 0;
}
