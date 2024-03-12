#include "rendering/sprite.h"

Sprite::Sprite(const uint8 textureIndex, const Vector2 textureCoordinates, const uint8 width, const uint8 height) : textureIndex(textureIndex), width(width), height(height) {
    this->textureCoordinates[0] = {textureCoordinates.x * 16, (textureCoordinates.y * 16 + static_cast<float>(height))};
    this->textureCoordinates[1] = {(textureCoordinates.x * 16 + static_cast<float>(width)), (textureCoordinates.y * 16 + static_cast<float>(height))};
    this->textureCoordinates[2] = {(textureCoordinates.x * 16 + static_cast<float>(width)), textureCoordinates.y * 16};
    this->textureCoordinates[3] = {textureCoordinates.x * 16, textureCoordinates.y * 16};
}