#include "platform/opengl/textureLoader.h"
#include "glad/glad.h"
#include "stb_image/stb_image.h"
#include <iostream>


uint32 TextureLoader::textureArrayId;


void TextureLoader::Load() {
    glActiveTexture(GL_TEXTURE0);
    glGenTextures(1, &textureArrayId);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayId);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, TEXTURE_ATLAS_WIDTH, TEXTURE_ATLAS_HEIGHT, TextureLayersCount, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    for (int32 i = 0; i < TextureLayersCount; i++) {
        unsigned char* pixels = LoadTextureData(textureAtlasNames[i]);
        glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, TEXTURE_ATLAS_WIDTH, TEXTURE_ATLAS_HEIGHT, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        stbi_image_free(pixels);
    }

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}


void TextureLoader::Unload() {
    glDeleteTextures(1, &textureArrayId);
}


unsigned char* TextureLoader::LoadTextureData(const std::string& filepath) {
    int32 width;
    int32 height;
    int32 channels;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(filepath.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if(!pixels) {
        //TODO Log instead of print to console
        std::cout << "Failed to load texture" << std::endl;
        exit(-1);
    }

    return pixels;
}
