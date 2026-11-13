#include "character/SFFReader.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

int main() {
    const char* path =
        "assets/characters/KOF-Rugal/Sprite.sff";

    std::vector<JFESFFSprite> sprites;

    if (!jfe_load_sff_table(path, &sprites)) {
        std::cout << "TABLE FAILED\n";
        return 1;
    }

    for (int i = 0; i < 3; i++) {
        const auto& s = sprites[i];

        std::cout << "\nSPRITE " << i << "\n";
        std::cout << "Group: " << s.group << "\n";
        std::cout << "Image: " << s.image << "\n";
        std::cout << "Size: " << s.width << "x" << s.height << "\n";
        std::cout << "Depth: " << int(s.colorDepth) << "\n";
        std::cout << "Compression: " << int(s.compression) << "\n";
        std::cout << "Linked Index: " << s.linkedIndex << "\n";
        std::cout << "Flags: " << s.flags << "\n";
        std::cout << "Data Offset: " << s.dataOffset << "\n";
        std::cout << "File Offset: " << s.dataFileOffset << "\n";
        std::cout << "Data Length: " << s.dataLength << "\n";

        std::ifstream f(path, std::ios::binary);
        f.seekg(s.dataFileOffset);

        unsigned char b[24]{};
        f.read(reinterpret_cast<char*>(b), 24);

        std::cout << "First Bytes: ";

        for (int j = 0; j < f.gcount(); j++)
            std::cout << std::hex << std::setw(2)
                      << std::setfill('0') << int(b[j]) << " ";

        std::cout << std::dec << "\n";
    }
}
