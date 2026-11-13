#pragma once

#include "character/JFECharacter.hpp"
#include <string>

struct JFEStateRuntime {
    int currentState = -1;
    int previousState = -1;
    int stateTime = 0;
    int animation = -1;
    int control = 0;
    int animationFrameIndex = 0;
    int animationFrameTime = 0;
    bool animationFinished = false;
    std::string stateType;
    std::string moveType;
    bool active = false;
};

struct JFEChangeStateInfo {
    bool found = false;
    int targetState = -1;
    std::string trigger;
};

extern "C" {
int jfe_state_runtime_enter(const JFECharacter*, JFEStateRuntime*, int);
void jfe_state_runtime_tick(JFEStateRuntime*);
int jfe_state_runtime_find_change_state(const JFECharacter*, int, JFEChangeStateInfo*);
int jfe_state_runtime_start_animation(const JFECharacter*, JFEStateRuntime*);
void jfe_state_runtime_tick_animation(const JFECharacter*, JFEStateRuntime*);
int jfe_state_runtime_apply_change_state(const JFECharacter*, JFEStateRuntime*);
int jfe_state_runtime_apply_change_anim(const JFECharacter*, JFEStateRuntime*);
int jfe_state_runtime_anim_time(const JFECharacter*, const JFEStateRuntime*);
int jfe_state_runtime_update(const JFECharacter*, JFEStateRuntime*);
}
