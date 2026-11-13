#pragma once

#include <string>
#include <vector>

struct JFECharacterFile {
    std::string key;
    std::string path;
};

struct JFECharacterDef {
    std::string name;
    std::string displayname;
    std::string author;
    std::string mugenversion;

    int localcoordX = 320;
    int localcoordY = 240;

    std::string sprite;
    std::string anim;
    std::string cmd;
    std::string cns;
    std::string snd;
    std::string st;

    std::vector<JFECharacterFile> files;
    std::vector<JFECharacterFile> palettes;
};

extern "C" {
int jfe_load_character_def(
    const char* filepath,
    JFECharacterDef* character
);
}
