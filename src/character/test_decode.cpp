#include "character/SFFReader.hpp"
#include <iostream>
#include <vector>
#include <cstdint>

int main() {
    const char* path =
        "assets/characters/KOF-Rugal/Sprite.sff";

    std::vector<JFESFFSprite> sprites;

    if (!jfe_load_sff_table(path, &sprites)) {
        std::cout << "SFF TABLE FAILED\n";
        return 1;
    }

    std::vector<uint8_t> pixels;

    // প্রথমে 9000,0 Sprite
    if (!jfe_decode_sff_sprite(path, &sprites[0], &pixels)) {
        std::cout << "FIRST SPRITE DECODE FAILED\n";
        return 1;
    }

    std::cout << "===== RUGAL PIXEL TEST =====\n";
    std::cout << "Sprite: "
              << sprites[0].group << ","
              << sprites[0].image << "\n";

    std::cout << "Width: " << sprites[0].width << "\n";
    std::cout << "Height: " << sprites[0].height << "\n";
    std::cout << "Decoded Pixels: " << pixels.size() << "\n";

    size_t nonzero = 0;

    for (uint8_t pixel : pixels) {
        if (pixel != 0) nonzero++;
    }

    std::cout << "Non-transparent Pixels: " << nonzero << "\n";
    std::cout << "JFE PIXEL DECODE TEST FINISHED\n";

    return 0;
}
