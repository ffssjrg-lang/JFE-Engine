#include "character/AIRReader.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

static std::string trimAIR(std::string s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return "";

    size_t b = s.find_last_not_of(" \t\r\n");
    return s.substr(a, b - a + 1);
}

static std::string lowerAIR(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });
    return s;
}

extern "C" int jfe_load_air(
    const char* filepath,
    std::vector<JFEAIRAction>* actions
) {
    if (!filepath || !actions) return 0;

    std::ifstream file(filepath);
    if (!file) return 0;

    actions->clear();

    JFEAIRAction* current = nullptr;
    std::string line;

    while (std::getline(file, line)) {
        line = trimAIR(line);

        if (line.empty() || line[0] == ';')
            continue;

        std::string lower = lowerAIR(line);

        if (lower.rfind("[begin action", 0) == 0) {
            size_t start = lower.find("action") + 6;
            size_t end = line.find(']', start);

            if (end == std::string::npos) {
                current = nullptr;
                continue;
            }

            std::string numberText =
                trimAIR(line.substr(start, end - start));

            try {
                size_t used = 0;
                int number = std::stoi(numberText, &used);

                if (used != numberText.size()) {
                    current = nullptr;
                    continue;
                }

                actions->push_back({});
                current = &actions->back();
                current->number = number;
            } catch (...) {
                current = nullptr;
            }

            continue;
        }

        if (!current) continue;

        if (lower == "loopstart") {
            current->loopStart = true;
            current->loopStartFrameIndex =
                static_cast<int>(current->frames.size());
            continue;
        }

        if (line.find('=') != std::string::npos ||
            line.find(':') != std::string::npos)
            continue;

        std::replace(line.begin(), line.end(), ',', ' ');

        std::istringstream stream(line);

        JFEAIRFrame frame;

        if (!(stream >> frame.group
                    >> frame.image
                    >> frame.x
                    >> frame.y
                    >> frame.duration))
            continue;

        std::getline(stream, frame.flags);
        frame.flags = trimAIR(frame.flags);

        current->frames.push_back(frame);
    }

    return static_cast<int>(actions->size());
}
