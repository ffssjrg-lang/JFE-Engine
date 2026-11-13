#pragma once

#include <string>

struct JFESNDInfo {
    std::string version;
    long long fileSize;
    bool valid;
};

extern "C" {
int jfe_snd_inspect(
    const char* filepath,
    JFESNDInfo* info
);
}
