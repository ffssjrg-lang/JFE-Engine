#include "character/CharacterDef.hpp"

#include <fstream>
#include <algorithm>
#include <cctype>

static std::string trimDEF(std::string s) {
    auto first = s.find_first_not_of(" \t\r\n");

    if (first == std::string::npos)
        return "";

    auto last = s.find_last_not_of(" \t\r\n");

    return s.substr(first, last - first + 1);
}

static std::string lowerDEF(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) {
            return std::tolower(c);
        });

    return s;
}

static std::string removeCommentDEF(std::string s) {
    bool quoted = false;

    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '"')
            quoted = !quoted;

        if (s[i] == ';' && !quoted) {
            s.erase(i);
            break;
        }
    }

    return trimDEF(s);
}

static std::string unquoteDEF(std::string s) {
    s = trimDEF(s);

    if (s.size() >= 2 &&
        s.front() == '"' &&
        s.back() == '"') {
        return s.substr(1, s.size() - 2);
    }

    return s;
}

extern "C" {

int jfe_load_character_def(
    const char* filepath,
    JFECharacterDef* character
) {
    if (!filepath || !character)
        return 0;

    std::ifstream file(filepath);

    if (!file.is_open())
        return 0;

    *character = JFECharacterDef{};

    std::string line;
    std::string section;

    while (std::getline(file, line)) {
        line = removeCommentDEF(line);

        if (line.empty())
            continue;

        if (line.front() == '[' &&
            line.back() == ']') {
            section = lowerDEF(
                trimDEF(line.substr(1, line.size() - 2))
            );
            continue;
        }

        auto pos = line.find('=');

        if (pos == std::string::npos)
            continue;

        std::string key =
            lowerDEF(trimDEF(line.substr(0, pos)));

        std::string value =
            unquoteDEF(line.substr(pos + 1));

        if (section == "info") {
            if (key == "name")
                character->name = value;

            else if (key == "displayname")
                character->displayname = value;

            else if (key == "author")
                character->author = value;

            else if (key == "mugenversion")
                character->mugenversion = value;

            else if (key == "localcoord") {
                auto comma = value.find(',');

                try {
                    character->localcoordX =
                        std::stoi(value.substr(0, comma));

                    if (comma != std::string::npos)
                        character->localcoordY =
                            std::stoi(value.substr(comma + 1));
                } catch (...) {}
            }
        }

        else if (section == "files") {
            JFECharacterFile entry{key, value};

            if (key.rfind("pal", 0) == 0) {
                character->palettes.push_back(entry);
            } else {
                character->files.push_back(entry);
            }

            if (key == "sprite")
                character->sprite = value;

            else if (key == "anim")
                character->anim = value;

            else if (key == "cmd")
                character->cmd = value;

            else if (key == "cns")
                character->cns = value;

            else if (key == "snd")
                character->snd = value;

            else if (key == "st")
                character->st = value;
        }
    }

    return character->name.empty() ? 0 : 1;
}

}
