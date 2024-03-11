#include "rendering/texture2D.h"

#include <iostream>
#include "stb_image/stb_image.h"
#include <glad/glad.h>


Texture2D::Texture2D(const std::string& filepath) {
    int32 bits;

    stbi_set_flip_vertically_on_load(true);
    unsigned char* pixels = stbi_load(filepath.c_str(), &width, &height, &bits, STBI_rgb_alpha);

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    //TODO Gamma correction with SRGB
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

    stbi_image_free(pixels);
}


Texture2D::~Texture2D() {
    glDeleteTextures(1, &id);
}


uint32 Texture2D::GetId() const {
    return id;
}


int32 Texture2D::GetWidth() const {
    return width;
}

int32 Texture2D::GetHeight() const {
    return height;
}
