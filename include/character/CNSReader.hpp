#pragma once

#include <string>
#include <vector>

struct JFECNSValue {
    std::string section;
    std::string key;
    std::string value;
};

extern "C" {
int jfe_load_cns(
    const char* filepath,
    std::vector<JFECNSValue>* values
);
}
