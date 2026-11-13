#include "character/STReader.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

static std::string trimST(std::string s) {
    size_t first = s.find_first_not_of(" \t\r\n");

    if (first == std::string::npos)
        return "";

    size_t last = s.find_last_not_of(" \t\r\n");

    return s.substr(first, last - first + 1);
}

static std::string lowerST(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });

    return s;
}

extern "C" int jfe_load_st(
    const char* filepath,
    std::vector<JFESTState>* states
) {
    if (!filepath || !states)
        return 0;

    std::ifstream file(filepath);

    if (!file.is_open())
        return 0;

    std::string line;

    JFESTState* current = nullptr;
    JFESTController* controller = nullptr;

    while (std::getline(file, line)) {
        line = trimST(line);

        if (line.empty() || line[0] == ';')
            continue;

        std::string low = lowerST(line);

        // State Definition
        if (low.rfind("[statedef ", 0) == 0) {
            size_t end = line.find(']');

            if (end == std::string::npos)
                continue;

            try {
                int number = std::stoi(
                    trimST(line.substr(10, end - 10))
                );

                states->push_back(JFESTState{});
                current = &states->back();
                current->number = number;

                controller = nullptr;
            }
            catch (...) {
                current = nullptr;
                controller = nullptr;
            }

            continue;
        }

        if (!current)
            continue;

        // Controller section
        if (low.rfind("[state ", 0) == 0) {
            current->controllers.push_back(
                JFESTController{}
            );

            controller = &current->controllers.back();

            continue;
        }

        // Ignore other sections
        if (line[0] == '[') {
            controller = nullptr;
            continue;
        }

        size_t pos = line.find('=');

        if (pos == std::string::npos)
            continue;

        std::string key = lowerST(
            trimST(line.substr(0, pos))
        );

        std::string value = trimST(
            line.substr(pos + 1)
        );

        // Remove inline comments
        size_t comment = value.find(';');

        if (comment != std::string::npos)
            value = trimST(value.substr(0, comment));

        if (controller) {
            if (key == "type") {
                controller->type = lowerST(value);
            }
            else if (key == "triggerall") {
                controller->triggerAll.push_back(value);
            }
            else if (key.rfind("trigger", 0) == 0) {
                controller->triggers.push_back(
                    key + "=" + value
                );
            }
            else {
                controller->parameters.push_back(
                    key + "=" + value
                );
            }
        }
        else {
            current->parameters.push_back(
                key + "=" + value
            );

            if (key == "type")
                current->type = value;
        }
    }

    return static_cast<int>(states->size());
}
