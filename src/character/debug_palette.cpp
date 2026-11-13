#include "character/SFFReader.hpp"
#include "character/PaletteReader.hpp"

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int main() {
    std::vector<JFESFFSprite> sprites;
    std::vector<uint8_t> pixels;
    std::vector<JFEColor> palette;

    const char* sff = "assets/characters/KOF-Rugal/Sprite.sff";
    const char* act = "assets/characters/KOF-Rugal/Palettes/1.act";

    if (!jfe_load_sff_table(sff, &sprites)) return 1;
    if (!jfe_decode_sff_sprite(sff, &sprites[1], &pixels)) return 2;
    if (!jfe_load_act_palette(act, &palette)) return 3;

    auto limits = std::minmax_element(pixels.begin(), pixels.end());

    std::set<int> indexes(pixels.begin(), pixels.end());

    int colored = 0;
    for (auto p : pixels) {
        auto c = palette[p];
        if (c.r || c.g || c.b) colored++;
    }

    std::cout << "Sprite: " << sprites[1].group
              << "," << sprites[1].image << "\n";
    std::cout << "Size: " << sprites[1].width
              << "x" << sprites[1].height << "\n";
    std::cout << "Pixel Min: " << (int)*limits.first << "\n";
    std::cout << "Pixel Max: " << (int)*limits.second << "\n";
    std::cout << "Unique Colors: " << indexes.size() << "\n";
    std::cout << "Non-black Pixels: " << colored << "\n";

    std::cout << "\nPalette entries 80-90:\n";
    for (int i = 80; i <= 90; i++) {
        auto c = palette[i];
        std::cout << i << ": "
                  << (int)c.r << ","
                  << (int)c.g << ","
                  << (int)c.b << "\n";
    }
}
