#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include "types.h"
#include <string>


// All texture atlases must be identical sizes to use Texture Arrays
constexpr int32 TEXTURE_ATLAS_WIDTH = 2240;
constexpr int32 TEXTURE_ATLAS_HEIGHT = 2400;

enum TextureLayerID : uint8 {
    Tiles = 0,
    Items = 1,
    Creatures = 2,
    Interface = 3,
    TextureLayersCount = 4
};

static std::string textureAtlasNames[TextureLayersCount] = {
    "assets/textures/tilesTest.png",
    "assets/textures/itemsTest.png",
    "assets/textures/creaturesTest.png",
    "assets/textures/interfaceTest.png"
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
