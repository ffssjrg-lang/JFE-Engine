#include "character/JFECharacter.hpp"
#include <iostream>

int main() {
    JFECharacter c;

    if (!jfe_load_character(
        "assets/characters/KOF-Rugal/KOF-Rugal.def", &c)) {
        std::cout << "CHARACTER LOAD FAILED\n";
        return 1;
    }

    const JFESFFSprite* sprite = nullptr;

    for (const auto& s : c.sprites) {
        if (s.group == 0 && s.image == 0) {
            sprite = &s;
            break;
        }
    }

    if (!sprite) {
        std::cout << "SPRITE NOT FOUND\n";
        return 1;
    }

    std::vector<uint8_t> pixels;

    std::cout << "Flags: " << sprite->flags << "\n";

    int result = jfe_decode_sff_sprite(
        "assets/characters/KOF-Rugal/Sprite.sff",
        sprite,
        &pixels
    );

    std::cout << "Decode Result: " << result << "\n";
    std::cout << "Decoded Pixels: " << pixels.size() << "\n";

    size_t visible = 0;

    for (uint8_t index : pixels) {
        if (index != 0) visible++;
    }

    std::cout << "Non-transparent Pixels: " << visible << "\n";

    return 0;
}
