#pragma once

#include <string>
#include <vector>

struct JFESTController {
    std::string type;
    std::vector<std::string> parameters;

    std::vector<std::string> triggers;
    std::vector<std::string> triggerAll;
};

struct JFESTState {
    int number = 0;
    std::string type;

    std::vector<std::string> parameters;
    std::vector<JFESTController> controllers;
};

extern "C" {
int jfe_load_st(
    const char* filepath,
    std::vector<JFESTState>* states
);
}
