#include "character/JFECharacter.hpp"

#include <algorithm>
#include <cctype>
#include <fstream>
#include <cstdio>
#include <set>

static std::string lowerKey(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });
    return s;
}

static std::string directoryOf(const std::string& path) {
    size_t p = path.find_last_of('/');
    if (p == std::string::npos) return ".";
    return path.substr(0, p);
}

static std::string resolvePath(
    const std::string& folder,
    const std::string& path
) {
    if (path.empty()) return "";
    if (path[0] == '/') return path;
    return folder + "/" + path;
}

static std::string findFile(
    const JFECharacterDef& def,
    const std::string& key
) {
    for (const auto& f : def.files) {
        if (lowerKey(f.key) == key)
            return f.path;
    }
    return "";
}

extern "C" int jfe_load_character(
    const char* defPath,
    JFECharacter* character
) {
    if (!defPath || !character) return 0;

    *character = JFECharacter{};

    if (!jfe_load_character_def(defPath, &character->def)) { fprintf(stderr, "FAILED: DEF\\n"); return 0; }

    character->folder = directoryOf(defPath);

    auto& d = character->def;

    std::string spr = d.sprite.empty()
        ? findFile(d, "spr") : d.sprite;

    std::string air = d.anim.empty()
        ? findFile(d, "anim") : d.anim;

    if (spr.empty() || air.empty()) return 0;

    std::string sffPath = resolvePath(character->folder, spr);
    std::string airPath = resolvePath(character->folder, air);

    if (!jfe_sff_inspect(sffPath.c_str(), &character->sffInfo)) { fprintf(stderr, "FAILED: SFF INSPECT\\n"); return 0; }

    if (!jfe_load_sff_table(sffPath.c_str(), &character->sprites)) { fprintf(stderr, "FAILED: SFF TABLE\\n"); return 0; }

    if (!jfe_load_air(airPath.c_str(), &character->animations)) { fprintf(stderr, "FAILED: AIR\\n"); return 0; }

    std::string cmd = d.cmd.empty()
        ? findFile(d, "cmd") : d.cmd;

    if (!cmd.empty()) {
        std::string path = resolvePath(character->folder, cmd);
        jfe_load_cmd(path.c_str(), &character->commands);
    }

    std::set<std::string> loadedCns;

    for (const auto& f : d.files) {
        std::string key = lowerKey(f.key);

        if (key.rfind("cns", 0) == 0 ||
            key.rfind("st", 0) == 0) {

            std::string path =
                resolvePath(character->folder, f.path);

            if (loadedCns.insert(path).second) {
                if (key.rfind("cns", 0) == 0)
                    jfe_load_cns(path.c_str(),
                                 &character->cnsValues);
                else
                    jfe_load_st(path.c_str(),
                                &character->states);
            }
        }
    }

    std::string snd = d.snd.empty()
        ? findFile(d, "snd") : d.snd;

    if (!snd.empty()) {
        std::string path = resolvePath(character->folder, snd);
        jfe_snd_inspect(path.c_str(), &character->sndInfo);
    }

    if (!d.palettes.empty()) {
        std::string path = resolvePath(
            character->folder,
            d.palettes[0].path
        );

        jfe_load_act_palette(path.c_str(), &character->palette);
    }

    character->loaded = true;
    return 1;
}
