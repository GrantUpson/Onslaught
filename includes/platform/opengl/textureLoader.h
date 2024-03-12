#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "types.h"
#include <unordered_map>


static constexpr int32 TEXTURE_ATLAS_WIDTH = 640;
static constexpr int32 TEXTURE_ATLAS_HEIGHT = 368;

enum TextureLayerID : uint8 {
    Tiles = 0,
    Items = 1,
    Creatures = 2,
    Interface = 3,
    TextureLayersCount = 4
};

struct TextureData {
    int32 width;
    int32 height;
    unsigned char* pixels;
};

static std::string textureAtlasNames[TextureLayersCount] = {
    "assets/textures/tiles.png",
    "assets/textures/items.png",
    "assets/textures/creatures.png",
    "assets/textures/interface.png"
};


class TextureLoader {
public:
    TextureLoader() = delete;
    static void Load();
    static void Unload();

private:
    static uint32 textureArrayId;

    static TextureData LoadTextureData(const std::string& filepath);
};


#endif
