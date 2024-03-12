#include "platform/opengl/textureLoader.h"
#include "glad/glad.h"
#include "stb_image/stb_image.h"
#include <iostream>


uint32 TextureLoader::textureArrayId;


// for (int32 i = 0; i < 1; i++) {
//     TextureData data = LoadTextureData(textureAtlasNames[i]);
//     assert(data.pixels != nullptr);
//     glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, i, TEXTURE_ATLAS_WIDTH, TEXTURE_ATLAS_HEIGHT, 1, GL_RGBA, GL_UNSIGNED_BYTE, data.pixels);
//     stbi_image_free(data.pixels);
// }


void TextureLoader::Load() {
    glActiveTexture(GL_TEXTURE1);
    glGenTextures(1, &textureArrayId);
    glBindTexture(GL_TEXTURE_2D_ARRAY, textureArrayId);
    glTexImage3D(GL_TEXTURE_2D_ARRAY, 0, GL_RGBA8, TEXTURE_ATLAS_WIDTH, TEXTURE_ATLAS_HEIGHT, TextureLayersCount, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    int32 channels;
    int32 width;
    int32 height;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(textureAtlasNames[0].c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if(!pixels) {
        exit(-3);
    }

    glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0, 0, 0, 0, TEXTURE_ATLAS_WIDTH, TEXTURE_ATLAS_HEIGHT, 1, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    stbi_image_free(pixels);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    GLenum errorCode;
    while ((errorCode = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (errorCode)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << std::endl;
    }
}


void TextureLoader::Unload() {
    glDeleteTextures(1, &textureArrayId);
}


TextureData TextureLoader::LoadTextureData(const std::string& filepath) {
    TextureData data {};
    int32 channels;

    stbi_set_flip_vertically_on_load(true);
    data.pixels = stbi_load(filepath.c_str(), &data.width, &data.height, &channels, STBI_rgb_alpha);

    if(!data.pixels) {
        exit(-3);
    }

    return data;
}
