#include "character/JFECharacter.hpp"
#include <iostream>

int main() {
    JFECharacter c;

    if (!jfe_load_character(
        "assets/characters/KOF-Rugal/KOF-Rugal.def", &c)) {
        std::cout << "LOAD FAILED\n";
        return 1;
    }

    const JFEAIRAction* action = nullptr;

    for (const auto& a : c.animations) {
        if (a.number == 0) {
            action = &a;
            break;
        }
    }

    if (!action || action->frames.empty()) {
        std::cout << "ACTION 0 NOT FOUND\n";
        return 1;
    }

    const auto& frame = action->frames[0];

    std::cout << "===== FIRST AIR FRAME =====\n";
    std::cout << "Group: " << frame.group << "\n";
    std::cout << "Image: " << frame.image << "\n";
    std::cout << "Duration: " << frame.duration << "\n";

    std::cout << "\n===== MATCHING SFF SPRITES =====\n";

    for (size_t i = 0; i < c.sprites.size(); i++) {
        const auto& s = c.sprites[i];

        if (s.group == frame.group && s.image == frame.image) {
            std::cout << "Index: " << i << "\n";
            std::cout << "Size: " << s.width << "x" << s.height << "\n";
            std::cout << "Axis: " << s.axisX << "," << s.axisY << "\n";
            std::cout << "Linked Index: " << s.linkedIndex << "\n";
            std::cout << "Compression: " << (int)s.compression << "\n";
            std::cout << "Data Length: " << s.dataLength << "\n";
            std::cout << "Palette Index: " << s.paletteIndex << "\n";
            std::cout << "Color Depth: " << (int)s.colorDepth << "\n";

            break;
        }
    }

    std::cout << "\nPalette Colors: " << c.palette.size() << "\n";
    return 0;
}
