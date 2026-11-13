#include "character/StateRuntime.hpp"

#include <string>
#include <algorithm>
#include <cctype>

static std::string lowerRuntime(std::string s) {
    std::transform(s.begin(), s.end(), s.begin(),
        [](unsigned char c) {
            return static_cast<char>(std::tolower(c));
        });
    return s;
}

static std::string trimRuntime(std::string s) {
    while (!s.empty() &&
        std::isspace(static_cast<unsigned char>(s.front())))
        s.erase(s.begin());

    while (!s.empty() &&
        std::isspace(static_cast<unsigned char>(s.back())))
        s.pop_back();

    return s;
}

static std::string getParameter(
    const std::vector<std::string>& parameters,
    const std::string& key
) {
    for (const auto& item : parameters) {
        size_t pos = item.find('=');
        if (pos == std::string::npos)
            continue;

        if (lowerRuntime(trimRuntime(item.substr(0, pos))) == key)
            return trimRuntime(item.substr(pos + 1));
    }
    return "";
}

static int getInteger(
    const std::vector<std::string>& parameters,
    const std::string& key,
    int defaultValue
) {
    std::string value = getParameter(parameters, key);
    if (value.empty())
        return defaultValue;

    try {
        return std::stoi(value);
    } catch (...) {
        return defaultValue;
    }
}

extern "C" int jfe_state_runtime_enter(
    const JFECharacter* character,
    JFEStateRuntime* runtime,
    int stateNumber
) {
    if (!character || !runtime)
        return 0;

    for (const auto& state : character->states) {
        if (state.number != stateNumber)
            continue;

        if (runtime->active)
            runtime->previousState = runtime->currentState;

        runtime->currentState = stateNumber;
        runtime->stateTime = 0;
        runtime->animation = getInteger(state.parameters, "anim", -1);
        runtime->control = getInteger(state.parameters, "ctrl", 0);
        runtime->stateType = state.type;
        runtime->moveType = getParameter(state.parameters, "movetype");
        runtime->animationFrameIndex = 0;
        runtime->animationFrameTime = 0;
        runtime->animationFinished = false;
        runtime->active = true;

        return 1;
    }

    return 0;
}

extern "C" void jfe_state_runtime_tick(JFEStateRuntime* runtime) {
    if (runtime && runtime->active)
        runtime->stateTime++;
}

extern "C" int jfe_state_runtime_find_change_state(
    const JFECharacter* character,
    int stateNumber,
    JFEChangeStateInfo* result
) {
    if (!character || !result)
        return 0;

    result->found = false;
    result->targetState = -1;
    result->trigger.clear();

    for (const auto& state : character->states) {
        if (state.number != stateNumber)
            continue;

        for (const auto& controller : state.controllers) {
            if (lowerRuntime(controller.type) != "changestate")
                continue;

            result->found = true;
            result->targetState = getInteger(controller.parameters, "value", -1);

            if (!controller.triggers.empty())
                result->trigger = controller.triggers[0];

            return 1;
        }
    }

    return 0;
}

extern "C" int jfe_state_runtime_start_animation(
    const JFECharacter* character,
    JFEStateRuntime* runtime
) {
    if (!character || !runtime)
        return 0;

    for (const auto& action : character->animations) {
        if (action.number != runtime->animation)
            continue;

        if (action.frames.empty())
            return 0;

        runtime->animationFrameIndex = 0;
        runtime->animationFrameTime = 0;
        runtime->animationFinished = false;
        return 1;
    }

    return 0;
}

extern "C" void jfe_state_runtime_tick_animation(
    const JFECharacter* character,
    JFEStateRuntime* runtime
) {
    if (!character || !runtime || runtime->animationFinished)
        return;

    for (const auto& action : character->animations) {
        if (action.number != runtime->animation)
            continue;

        if (runtime->animationFrameIndex < 0 ||
            runtime->animationFrameIndex >=
            static_cast<int>(action.frames.size()))
            return;

        const auto& frame = action.frames[runtime->animationFrameIndex];

        if (frame.duration < 0)
            return;

        runtime->animationFrameTime++;

        if (runtime->animationFrameTime < frame.duration)
            return;

        runtime->animationFrameTime = 0;
        runtime->animationFrameIndex++;

        if (runtime->animationFrameIndex >=
            static_cast<int>(action.frames.size())) {
            if (action.loopStart &&
                action.loopStartFrameIndex >= 0 &&
                action.loopStartFrameIndex <
                static_cast<int>(action.frames.size())) {
                runtime->animationFrameIndex =
                    action.loopStartFrameIndex;
            } else {
                runtime->animationFinished = true;
            }
        }

        return;
    }
}

extern "C" int jfe_state_runtime_anim_time(
    const JFECharacter* character,
    const JFEStateRuntime* runtime
) {
    if (!character || !runtime)
        return -1;

    if (runtime->animationFinished)
        return 0;

    for (const auto& action : character->animations) {
        if (action.number != runtime->animation)
            continue;

        if (action.loopStart)
            return -1;

        if (runtime->animationFrameIndex < 0 ||
            runtime->animationFrameIndex >=
            static_cast<int>(action.frames.size()))
            return -1;

        int remaining = 0;

        for (int i = runtime->animationFrameIndex;
             i < static_cast<int>(action.frames.size()); i++) {
            int duration = action.frames[i].duration;

            if (duration < 0)
                return -1;

            if (i == runtime->animationFrameIndex)
                duration -= runtime->animationFrameTime;

            remaining += duration;
        }

        return remaining;
    }

    return -1;
}

extern "C" int jfe_state_runtime_apply_change_anim(
    const JFECharacter* character,
    JFEStateRuntime* runtime
) {
    if (!character || !runtime || !runtime->active)
        return 0;

    for (const auto& state : character->states) {
        if (state.number != runtime->currentState)
            continue;

        for (const auto& controller : state.controllers) {
            if (lowerRuntime(controller.type) != "changeanim")
                continue;

            int targetAnim = getInteger(controller.parameters, "value", -1);
            if (targetAnim < 0)
                continue;

            bool matched = false;

            for (const auto& trigger : controller.triggers) {
                size_t pos = trigger.find('=');
                if (pos == std::string::npos)
                    continue;

                std::string expression =
                    lowerRuntime(trimRuntime(trigger.substr(pos + 1)));

                expression.erase(
                    std::remove_if(expression.begin(), expression.end(),
                        [](unsigned char c) {
                            return std::isspace(c);
                        }),
                    expression.end()
                );

                if (expression.find("anim!=[0,1]") != std::string::npos &&
                    runtime->animation != 0 &&
                    runtime->animation != 1 &&
                    runtime->animation != 5) {
                    matched = true;
                    break;
                }

                if (expression == "anim=5&&animtime=0" &&
                    runtime->animation == 5 &&
                    jfe_state_runtime_anim_time(character, runtime) == 0) {
                    matched = true;
                    break;
                }
            }

            if (!matched || runtime->animation == targetAnim)
                continue;

            runtime->animation = targetAnim;

            if (jfe_state_runtime_start_animation(character, runtime))
                return 1;
        }
    }

    return 0;
}

extern "C" int jfe_state_runtime_apply_change_state(
    const JFECharacter* character,
    JFEStateRuntime* runtime
) {
    if (!character || !runtime || !runtime->active)
        return 0;

    for (const auto& state : character->states) {
        if (state.number != runtime->currentState)
            continue;

        for (const auto& controller : state.controllers) {
            if (lowerRuntime(controller.type) != "changestate")
                continue;

            int targetState = getInteger(controller.parameters, "value", -1);
            if (targetState < 0)
                continue;

            bool matched = false;

            for (const auto& trigger : controller.triggers) {
                size_t pos = trigger.find('=');
                if (pos == std::string::npos)
                    continue;

                std::string expression =
                    lowerRuntime(trimRuntime(trigger.substr(pos + 1)));

                expression.erase(
                    std::remove_if(expression.begin(), expression.end(),
                        [](unsigned char c) {
                            return std::isspace(c);
                        }),
                    expression.end()
                );

                if (expression == "animtime=0" &&
                    jfe_state_runtime_anim_time(character, runtime) == 0) {
                    matched = true;
                    break;
                }
            }

            if (!matched)
                continue;

            if (!jfe_state_runtime_enter(character, runtime, targetState))
                return 0;

            jfe_state_runtime_start_animation(character, runtime);
            return 1;
        }
    }

    return 0;
}

extern "C" int jfe_state_runtime_update(
    const JFECharacter* character,
    JFEStateRuntime* runtime
) {
    if (!character || !runtime || !runtime->active)
        return 0;

    jfe_state_runtime_tick(runtime);
    jfe_state_runtime_apply_change_anim(character, runtime);
    jfe_state_runtime_tick_animation(character, runtime);

    return jfe_state_runtime_apply_change_state(character, runtime);
}
