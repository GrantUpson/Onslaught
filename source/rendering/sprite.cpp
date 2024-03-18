#include "rendering/sprite.h"

static constexpr uint16 TILE_SIZE = 16;

/**
 * Note: Texture coordinates are implemented with 0,0 as the top left of the texture atlas with the Y axis going down.
 * @param textureIndex The layer in the Texture Array to use.
 * @param textureCoordinates The X and Y coordinates of the sprite in the texture atlas with the origin being the top left vertex.
 * @param width The width of the sprite in pixels.
 * @param height The height of the sprite in pixels.
 */
Sprite::Sprite(const uint8 textureIndex, const Vector2 textureCoordinates, const uint8 width, const uint8 height) : textureIndex(textureIndex), width(width), height(height) {
    this->textureCoordinates[0] = {textureCoordinates.x * TILE_SIZE, textureCoordinates.y * TILE_SIZE};
    this->textureCoordinates[1] = {(textureCoordinates.x * TILE_SIZE + static_cast<float>(width)), textureCoordinates.y * TILE_SIZE};
    this->textureCoordinates[2] = {(textureCoordinates.x * TILE_SIZE + static_cast<float>(width)), (textureCoordinates.y * TILE_SIZE + static_cast<float>(height))};
    this->textureCoordinates[3] = {textureCoordinates.x * TILE_SIZE, (textureCoordinates.y * TILE_SIZE + static_cast<float>(height))};
}