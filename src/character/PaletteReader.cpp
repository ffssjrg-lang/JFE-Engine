#include "character/PaletteReader.hpp"

#include <fstream>

extern "C" {
int jfe_load_act_palette(
    const char* filepath,
    std::vector<JFEColor>* palette
) {
    if (!filepath || !palette)
        return 0;

    std::ifstream file(filepath, std::ios::binary);

    if (!file)
        return 0;

    unsigned char data[768];

    file.read(
        reinterpret_cast<char*>(data),
        sizeof(data)
    );

    if (file.gcount() != 768)
        return 0;

    palette->clear();
    palette->reserve(256);

    for (int i = 0; i < 256; i++) {
        JFEColor color;

        color.r = data[i * 3];
        color.g = data[i * 3 + 1];
        color.b = data[i * 3 + 2];
        color.a = (i == 0) ? 0 : 255;

        palette->push_back(color);
    }

    return 1;
}
}
