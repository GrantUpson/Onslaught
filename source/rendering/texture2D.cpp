#include "rendering/texture2D.h"
#include <glad/glad.h>


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
