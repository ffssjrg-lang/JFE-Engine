#include "character/CMDReader.hpp"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>

static std::string trimCMD(std::string s) {
    auto first = s.find_first_not_of(" \t\r\n");

    if (first == std::string::npos)
        return "";

    auto last = s.find_last_not_of(" \t\r\n");

    return s.substr(first, last - first + 1);
}

static std::string lowerCMD(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) {
            return std::tolower(c);
        });

    return s;
}

extern "C" {

int jfe_load_cmd(
    const char* filepath,
    std::vector<JFECMDCommand>* commands
) {
    if (!filepath || !commands)
        return 0;

    std::ifstream file(filepath);

    if (!file.is_open())
        return 0;

    commands->clear();

    std::string line;
    bool inCommand = false;

    JFECMDCommand current = {};
    bool hasName = false;
    bool hasCommand = false;

    while (std::getline(file, line)) {
        line = trimCMD(line);

        if (line.empty() || line[0] == ';')
            continue;

        if (line[0] == '[' && line.back() == ']') {
            if (inCommand && hasName && hasCommand)
                commands->push_back(current);

            std::string section =
                lowerCMD(line.substr(1, line.size() - 2));

            inCommand = section == "command";

            current = {};
            current.time = 15;
            current.bufferTime = 1;

            hasName = false;
            hasCommand = false;

            continue;
        }

        if (!inCommand)
            continue;

        auto pos = line.find('=');

        if (pos == std::string::npos)
            continue;

        std::string key =
            lowerCMD(trimCMD(line.substr(0, pos)));

        std::string value =
            trimCMD(line.substr(pos + 1));

        auto comment = value.find(';');

        if (comment != std::string::npos)
            value = trimCMD(value.substr(0, comment));

        if (key == "name") {
            current.name = value;
            hasName = true;
        }

        if (key == "command") {
            current.command = value;
            hasCommand = true;
        }

        if (key == "time") {
            try {
                current.time = std::stoi(value);
            } catch (...) {}
        }

        if (key == "buffer.time") {
            try {
                current.bufferTime = std::stoi(value);
            } catch (...) {}
        }
    }

    if (inCommand && hasName && hasCommand)
        commands->push_back(current);

    return static_cast<int>(commands->size());
}

}
