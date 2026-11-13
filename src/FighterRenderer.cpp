#include "character/JFECharacter.hpp"
#include "character/StateRuntime.hpp"

#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>

extern "C" {
void jfe_draw_rect(int, int, int, int, int, int, int, int);

void jfe_draw_rgba_sprite(
    int,
    const unsigned char*,
    int, int,
    int, int,
    int, int
);
}

static std::unordered_map<std::string, std::vector<uint8_t>> rgbaCache;
static std::unordered_map<std::string, int> textureIds;
static int nextTextureId = 1;

extern "C" {

int jfe_draw_character_sprite(
    const JFECharacter* character,
    const JFEStateRuntime* runtime,
    int x,
    int y,
    int scale
) {
    if (!character || !runtime || !character->loaded ||
        scale <= 0 || character->palette.empty())
        return 0;

    const JFEAIRAction* action = nullptr;

    for (const auto& a : character->animations) {
        if (a.number == runtime->animation) {
            action = &a;
            break;
        }
    }

    if (!action || runtime->animationFrameIndex < 0 ||
        runtime->animationFrameIndex >=
        static_cast<int>(action->frames.size()))
        return 0;

    const auto& frame =
        action->frames[runtime->animationFrameIndex];

    size_t spriteIndex = character->sprites.size();

    for (size_t i = 0; i < character->sprites.size(); i++) {
        const auto& s = character->sprites[i];

        if (s.group == frame.group && s.image == frame.image) {
            spriteIndex = i;
            break;
        }
    }

    if (spriteIndex == character->sprites.size())
        return 0;

    const auto& sprite = character->sprites[spriteIndex];

    std::string spritePath =
        character->folder + "/" + character->def.sprite;

    std::string key =
        character->folder + "|" +
        character->def.sprite + "|" +
        std::to_string(spriteIndex);

    auto cached = rgbaCache.find(key);

    if (cached == rgbaCache.end()) {
        std::vector<uint8_t> indexed;

        const JFESFFSprite* decodeSprite = &sprite;

        if (sprite.dataLength == 0 &&
            sprite.linkedIndex < character->sprites.size()) {
            decodeSprite =
                &character->sprites[sprite.linkedIndex];
        }

        if (!jfe_decode_sff_sprite(
            spritePath.c_str(), decodeSprite, &indexed))
            return 0;

        size_t pixelCount =
            size_t(sprite.width) * sprite.height;

        if (indexed.size() != pixelCount)
            return 0;

        std::vector<uint8_t> rgba(pixelCount * 4);

        for (size_t i = 0; i < pixelCount; i++) {
            uint8_t index = indexed[i];

            if (index >= character->palette.size()) {
                rgba[i * 4 + 0] = 0;
                rgba[i * 4 + 1] = 0;
                rgba[i * 4 + 2] = 0;
                rgba[i * 4 + 3] = 0;
                continue;
            }

            const auto& color = character->palette[index];

            rgba[i * 4 + 0] = color.r;
            rgba[i * 4 + 1] = color.g;
            rgba[i * 4 + 2] = color.b;
            rgba[i * 4 + 3] = color.a;
        }

        cached = rgbaCache.emplace(key, std::move(rgba)).first;
    }

    auto texture = textureIds.find(key);

    if (texture == textureIds.end()) {
        texture = textureIds.emplace(
            key, nextTextureId++
        ).first;
    }

    int drawWidth = sprite.width * scale;
    int drawHeight = sprite.height * scale;

    int drawX = x + (frame.x - sprite.axisX) * scale;
    int drawY = y + (frame.y - sprite.axisY) * scale;

    jfe_draw_rgba_sprite(
        texture->second,
        cached->second.data(),
        sprite.width,
        sprite.height,
        drawX,
        drawY,
        drawWidth,
        drawHeight
    );

    return 1;
}

void jfe_draw_fighter(int x, int y, int player) {
    int r = player == 1 ? 30 : 220;
    int g = player == 1 ? 120 : 50;
    int b = player == 1 ? 255 : 50;

    jfe_draw_rect(x + 15, y, 30, 30, 230, 190, 150, 255);
    jfe_draw_rect(x + 10, y + 30, 40, 55, r, g, b, 255);
    jfe_draw_rect(x, y + 38, 10, 35, r, g, b, 255);
    jfe_draw_rect(x + 50, y + 38, 10, 35, r, g, b, 255);
    jfe_draw_rect(x + 12, y + 85, 15, 35, 40, 40, 40, 255);
    jfe_draw_rect(x + 33, y + 85, 15, 35, 40, 40, 40, 255);
}

void jfe_draw_health_bar(int x, int y, int health, int player) {
    if (health < 0) health = 0;
    if (health > 100) health = 100;

    jfe_draw_rect(x, y, 200, 16, 80, 20, 20, 255);

    int green = player == 1 ? 220 : 50;
    jfe_draw_rect(x, y, health * 2, 16, 30, green, 50, 255);
}

}
