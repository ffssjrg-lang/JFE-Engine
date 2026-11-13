#pragma once

#include <string>
#include <vector>
#include <cstdint>

struct JFESFFInfo {
    std::string version;
    long long fileSize = 0;
    bool valid = false;
};

struct JFESFFSprite {
    uint16_t group;
    uint16_t image;
    uint16_t width;
    uint16_t height;
    int16_t axisX;
    int16_t axisY;
    uint16_t linkedIndex;
    uint8_t compression;
    uint8_t colorDepth;
    uint32_t dataOffset;
    uint32_t dataFileOffset;
    uint32_t dataLength;
    uint16_t paletteIndex;
    uint16_t flags;
};

extern "C" {
int jfe_sff_inspect(const char* filepath, JFESFFInfo* info);

int jfe_load_sff_table(
    const char* filepath,
    std::vector<JFESFFSprite>* sprites
);

int jfe_decode_sff_sprite(
    const char* filepath,
    const JFESFFSprite* sprite,
    std::vector<uint8_t>* pixels
);
}
