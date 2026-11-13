#pragma once

#include <string>
#include <vector>

struct JFECMDCommand {
    std::string name;
    std::string command;
    int time;
    int bufferTime;
};

extern "C" {
int jfe_load_cmd(
    const char* filepath,
    std::vector<JFECMDCommand>* commands
);
}
