#pragma once

#include <string>
#include <vector>
#include <cstdint>

struct JFEColor {
    uint8_t r;
    uint8_t g;
    uint8_t b;
    uint8_t a;
};

extern "C" {
int jfe_load_act_palette(
    const char* filepath,
    std::vector<JFEColor>* palette
);
}
