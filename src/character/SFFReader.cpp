#include "character/SFFReader.hpp"

#include <fstream>
#include <array>
#include <cstring>
#include <limits>

static uint16_t read16(const unsigned char* p) {
    return uint16_t(p[0]) | (uint16_t(p[1]) << 8);
}

static int16_t readS16(const unsigned char* p) {
    return static_cast<int16_t>(read16(p));
}

static uint32_t read32(const unsigned char* p) {
    return uint32_t(p[0]) |
           (uint32_t(p[1]) << 8) |
           (uint32_t(p[2]) << 16) |
           (uint32_t(p[3]) << 24);
}

int jfe_sff_inspect(const char* filepath, JFESFFInfo* info) {
    if (!filepath || !info) return 0;

    std::ifstream file(filepath, std::ios::binary);
    if (!file) return 0;

    std::array<unsigned char, 512> header{};

    file.read(reinterpret_cast<char*>(header.data()), header.size());
    if (file.gcount() != 512) return 0;

    const char signature[] = "ElecbyteSpr";

    if (!std::equal(
        signature, signature + 11, header.begin()
    )) return 0;

    file.seekg(0, std::ios::end);
    auto size = file.tellg();

    if (size < 512) return 0;

    info->version =
        std::to_string(header[15]) + "." +
        std::to_string(header[14]) + "." +
        std::to_string(header[13]) + "." +
        std::to_string(header[12]);

    info->fileSize = static_cast<long long>(size);
    info->valid = true;

    return 1;
}

int jfe_load_sff_table(
    const char* filepath,
    std::vector<JFESFFSprite>* sprites
) {
    if (!filepath || !sprites) return 0;

    std::ifstream file(filepath, std::ios::binary);
    if (!file) return 0;

    file.seekg(0, std::ios::end);
    auto end = file.tellg();

    if (end < 512) return 0;

    uint64_t fileSize = static_cast<uint64_t>(end);

    std::array<unsigned char, 512> header{};

    file.seekg(0);
    file.read(reinterpret_cast<char*>(header.data()), 512);

    if (file.gcount() != 512) return 0;

    if (std::memcmp(header.data(), "ElecbyteSpr", 11) != 0)
        return 0;

    if (header[15] != 2) return 0;

    uint32_t spriteOffset = read32(&header[36]);
    uint32_t spriteCount  = read32(&header[40]);
    uint32_t paletteOffset = read32(&header[44]);
    uint32_t paletteCount  = read32(&header[48]);
    uint32_t ldataOffset = read32(&header[52]);
    uint32_t ldataLength = read32(&header[56]);
    uint32_t tdataOffset = read32(&header[60]);
    uint32_t tdataLength = read32(&header[64]);

    (void)paletteOffset;
    (void)paletteCount;

    constexpr uint64_t ENTRY_SIZE = 28;

    if (spriteCount > 100000) return 0;

    uint64_t tableEnd =
        uint64_t(spriteOffset) +
        uint64_t(spriteCount) * ENTRY_SIZE;

    if (spriteOffset < 512 ||
        tableEnd > fileSize ||
        tableEnd > ldataOffset) {
        return 0;
    }

    std::vector<JFESFFSprite> result;
    result.reserve(spriteCount);

    for (uint32_t i = 0; i < spriteCount; i++) {
        unsigned char entry[28]{};

        uint64_t position =
            uint64_t(spriteOffset) + uint64_t(i) * ENTRY_SIZE;

        file.seekg(static_cast<std::streamoff>(position));

        file.read(reinterpret_cast<char*>(entry), 28);

        if (file.gcount() != 28) return 0;

        JFESFFSprite s{};

        s.group       = read16(&entry[0]);
        s.image       = read16(&entry[2]);
        s.width       = read16(&entry[4]);
        s.height      = read16(&entry[6]);
        s.axisX       = readS16(&entry[8]);
        s.axisY       = readS16(&entry[10]);
        s.linkedIndex = read16(&entry[12]);
        s.compression = entry[14];
        s.colorDepth  = entry[15];
        s.dataOffset  = read32(&entry[16]);
        s.dataLength  = read32(&entry[20]);
        s.paletteIndex = read16(&entry[24]);
        s.flags       = read16(&entry[26]);

        uint64_t blockOffset =
            (s.flags & 1) ? tdataOffset : ldataOffset;

        uint64_t blockLength =
            (s.flags & 1) ? tdataLength : ldataLength;

        if (s.dataOffset > blockLength ||
            s.dataLength > blockLength - s.dataOffset)
            return 0;

        uint64_t absolute = blockOffset + s.dataOffset;

        if (absolute > fileSize ||
            s.dataLength > fileSize - absolute)
            return 0;

        s.dataFileOffset = static_cast<uint32_t>(absolute);

        result.push_back(s);
    }

    *sprites = std::move(result);

    return 1;
}




// Decode SFF v2 RAW and RLE8 indexed pixels.
int jfe_decode_sff_sprite(
    const char* filepath,
    const JFESFFSprite* sprite,
    std::vector<uint8_t>* pixels
) {
    if (!filepath || !sprite || !pixels) return 0;

    if (!sprite->width || !sprite->height ||
        sprite->width > 4096 || sprite->height > 4096)
        return 0;

    if (sprite->colorDepth != 8) return 0;

    size_t expected =
        size_t(sprite->width) * size_t(sprite->height);

    std::ifstream file(filepath, std::ios::binary);
    if (!file) return 0;

    std::vector<unsigned char> data(sprite->dataLength);

    file.seekg(sprite->dataFileOffset);
    file.read(reinterpret_cast<char*>(data.data()), data.size());

    if (static_cast<size_t>(file.gcount()) != data.size())
        return 0;

    std::vector<uint8_t> output;
    output.reserve(expected);

    if (sprite->compression == 0) {
        if (data.size() != expected) return 0;
        output.assign(data.begin(), data.end());
    }
    else if (sprite->compression == 2) {
        if (data.size() < 4) return 0;

        uint32_t decodedSize =
            uint32_t(data[0]) |
            (uint32_t(data[1]) << 8) |
            (uint32_t(data[2]) << 16) |
            (uint32_t(data[3]) << 24);

        if (decodedSize != expected) return 0;

        size_t pos = 4;

        while (pos < data.size() && output.size() < expected) {
            unsigned char value = data[pos++];

            if ((value & 0xC0) == 0x40) {
                size_t run = value & 0x3F;
                if (run == 0) run = 256;

                if (pos >= data.size()) return 0;

                unsigned char color = data[pos++];

                if (run > expected - output.size())
                    return 0;

                output.insert(output.end(), run, color);
            } else {
                output.push_back(value);
            }
        }

        if (output.size() != expected) return 0;
    }
    else {
        return 0;
    }

    *pixels = std::move(output);
    return 1;
}
