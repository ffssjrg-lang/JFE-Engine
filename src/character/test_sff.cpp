#include "character/SFFReader.hpp"
#include <iostream>
#include <vector>

int main() {
    const char* path =
        "assets/characters/KOF-Rugal/Sprite.sff";

    std::vector<JFESFFSprite> sprites;

    if (!jfe_load_sff_table(path, &sprites)) {
        std::cout << "SFF TABLE LOAD FAILED\n";
        return 1;
    }

    std::cout << "===== RUGAL SFF SPRITES =====\n";
    std::cout << "Total Sprites: " << sprites.size() << "\n";

    for (size_t i = 0; i < sprites.size() && i < 15; i++) {
        const auto& s = sprites[i];

        std::cout
            << "Group: " << s.group
            << " | Image: " << s.image
            << " | Size: " << s.width << "x" << s.height
            << " | Axis: " << s.axisX << "," << s.axisY
            << " | Format: " << int(s.compression)
            << " | Data: " << s.dataLength
            << "\n";
    }

    std::cout << "JFE SFF TABLE TEST SUCCESS\n";
    return 0;
}
