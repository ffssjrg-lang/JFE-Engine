#include "character/CNSReader.hpp"

#include <fstream>
#include <algorithm>
#include <cctype>

static std::string trimCNS(std::string s) {
    auto first = s.find_first_not_of(" \t\r\n");

    if (first == std::string::npos)
        return "";

    auto last = s.find_last_not_of(" \t\r\n");

    return s.substr(first, last - first + 1);
}

static std::string lowerCNS(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) {
            return std::tolower(c);
        });

    return s;
}

extern "C" {

int jfe_load_cns(
    const char* filepath,
    std::vector<JFECNSValue>* values
) {
    if (!filepath || !values)
        return 0;

    std::ifstream file(filepath);

    if (!file.is_open())
        return 0;

    values->clear();

    std::string line;
    std::string section;

    while (std::getline(file, line)) {
        line = trimCNS(line);

        if (line.empty() || line[0] == ';')
            continue;

        if (line[0] == '[' && line.back() == ']') {
            section = trimCNS(
                line.substr(1, line.size() - 2)
            );

            continue;
        }

        auto pos = line.find('=');

        if (pos == std::string::npos)
            continue;

        std::string key =
            trimCNS(line.substr(0, pos));

        std::string value =
            trimCNS(line.substr(pos + 1));

        auto comment = value.find(';');

        if (comment != std::string::npos)
            value = trimCNS(value.substr(0, comment));

        values->push_back({
            section,
            key,
            value
        });
    }

    return static_cast<int>(values->size());
}

}
