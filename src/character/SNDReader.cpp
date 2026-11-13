#include "character/SNDReader.hpp"

#include <fstream>
#include <cstdint>

extern "C" {

int jfe_snd_inspect(
    const char* filepath,
    JFESNDInfo* info
) {
    if (!filepath || !info)
        return 0;

    std::ifstream file(filepath, std::ios::binary);

    if (!file.is_open())
        return 0;

    char signature[11];

    file.read(signature, 11);

    if (file.gcount() != 11)
        return 0;

    const char expected[11] = {
        'E','l','e','c','b','y','t','e','S','n','d'
    };

    for (int i = 0; i < 11; i++) {
        if (signature[i] != expected[i]) {
            info->valid = false;
            return 0;
        }
    }

    unsigned char version[4] = {};

    file.read(reinterpret_cast<char*>(version), 4);

    if (file.gcount() != 4)
        return 0;

    file.seekg(0, std::ios::end);

    info->fileSize = file.tellg();

    info->version =
        std::to_string(version[0]) + "." +
        std::to_string(version[1]) + "." +
        std::to_string(version[2]) + "." +
        std::to_string(version[3]);

    info->valid = true;

    return 1;
}

}
