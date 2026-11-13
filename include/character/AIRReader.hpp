#pragma once

#include <string>
#include <vector>

struct JFEAIRFrame {
    int group = 0;
    int image = 0;
    int x = 0;
    int y = 0;
    int duration = 0;
    std::string flags;
};

struct JFEAIRAction {
    int number = 0;
    bool loopStart = false;
    int loopStartFrameIndex = -1;
    std::vector<JFEAIRFrame> frames;
};

extern "C" {
int jfe_load_air(
    const char* filepath,
    std::vector<JFEAIRAction>* actions
);
}
