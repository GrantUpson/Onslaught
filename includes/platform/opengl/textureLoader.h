#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "types.h"
#include <string>


//All texture atlases must be identicl sizes to use Texture Arrays
static constexpr int32 TEXTURE_ATLAS_WIDTH = 640;
static constexpr int32 TEXTURE_ATLAS_HEIGHT = 368;

enum TextureLayerID : uint8 {
    Tiles = 0,
    Items = 1,
    Creatures = 2,
    Interface = 3,
    TextureLayersCount = 4
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
    static unsigned char* LoadTextureData(const std::string& filepath);
};


#endif
