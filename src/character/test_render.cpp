#include "character/SFFReader.hpp"
#include "character/PaletteReader.hpp"

#include <iostream>
#include <fstream>
#include <vector>

int main() {
    const char* sff =
        "assets/characters/KOF-Rugal/Sprite.sff";

    const char* act =
        "assets/characters/KOF-Rugal/Palettes/1.act";

    std::vector<JFESFFSprite> sprites;
    std::vector<uint8_t> pixels;
    std::vector<JFEColor> palette;

    if (!jfe_load_sff_table(sff, &sprites)) {
        std::cout << "SFF TABLE FAILED\n";
        return 1;
    }

    if (!jfe_decode_sff_sprite(sff, &sprites[1], &pixels)) {
        std::cout << "PIXEL DECODE FAILED\n";
        return 1;
    }

    if (!jfe_load_act_palette(act, &palette)) {
        std::cout << "PALETTE LOAD FAILED\n";
        return 1;
    }

    int width = sprites[1].width;
    int height = sprites[1].height;

    std::ofstream out(
        "build/characters/rugal_sprite.ppm",
        std::ios::binary
    );

    out << "P6\n" << width << " " << height << "\n255\n";

    for (int i = 0; i < width * height; i++) {
        JFEColor c = palette[pixels[i]];

        unsigned char rgb[3] = {
            c.r, c.g, c.b
        };

        out.write(
            reinterpret_cast<char*>(rgb),
            3
        );
    }

    out.close();

    std::cout << "RUGAL COLOR IMAGE CREATED\n";
    std::cout << "Size: " << width << "x" << height << "\n";
    std::cout << "File: build/characters/rugal_sprite.ppm\n";

    return 0;
}
