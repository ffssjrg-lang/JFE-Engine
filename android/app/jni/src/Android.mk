LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/$(SDL_PATH)/include \
    $(LOCAL_PATH)/../../../../include \
    $(LOCAL_PATH)/../../../../src

LOCAL_CPPFLAGS := -std=c++17 -fexceptions -frtti

LOCAL_SRC_FILES := \
    jfe_android_main.cpp \
    ../../../../src/EngineCore.cpp \
    ../../../../src/FighterRenderer.cpp \
    ../../../../src/GameLoop.cpp \
    ../../../../src/GameScene.cpp \
    ../../../../src/GraphicsCore.cpp \
    ../../../../src/character/AIRReader.cpp \
    ../../../../src/character/CMDReader.cpp \
    ../../../../src/character/CNSReader.cpp \
    ../../../../src/character/CharacterDef.cpp \
    ../../../../src/character/JFECharacter.cpp \
    ../../../../src/character/PaletteReader.cpp \
    ../../../../src/character/SFFReader.cpp \
    ../../../../src/character/SNDReader.cpp \
    ../../../../src/character/STReader.cpp \
    ../../../../src/character/StateRuntime.cpp

LOCAL_SHARED_LIBRARIES := SDL2

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -lOpenSLES -llog -landroid

include $(BUILD_SHARED_LIBRARY)
