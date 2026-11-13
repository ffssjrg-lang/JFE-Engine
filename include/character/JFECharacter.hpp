#pragma once

#include "CharacterDef.hpp"
#include "SFFReader.hpp"
#include "AIRReader.hpp"
#include "CMDReader.hpp"
#include "CNSReader.hpp"
#include "STReader.hpp"
#include "SNDReader.hpp"
#include "PaletteReader.hpp"

#include <string>
#include <vector>

struct JFECharacter {
    JFECharacterDef def;

    JFESFFInfo sffInfo;
    JFESNDInfo sndInfo;

    std::vector<JFESFFSprite> sprites;
    std::vector<JFEAIRAction> animations;
    std::vector<JFECMDCommand> commands;
    std::vector<JFECNSValue> cnsValues;
    std::vector<JFESTState> states;
    std::vector<JFEColor> palette;

    std::string folder;
    bool loaded = false;
};

extern "C" {
int jfe_load_character(
    const char* defPath,
    JFECharacter* character
);
}
