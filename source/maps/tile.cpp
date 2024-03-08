#include "maps/tile.h"


Tile::Tile(const Biome biome, const uint32 properties, const Vector2& textureCoordinates) : biome(biome), properties(properties) {
    this->textureCoordinates[0] = {textureCoordinates.x * width / sheetWidth, (textureCoordinates.y + 1) * height / sheetHeight};
    this->textureCoordinates[1] = {(textureCoordinates.x + 1) * width / sheetWidth, (textureCoordinates.y + 1) * height / sheetHeight};
    this->textureCoordinates[2] = {(textureCoordinates.x + 1) * width / sheetWidth, textureCoordinates.y * height / sheetHeight};
    this->textureCoordinates[3] = {textureCoordinates.x * width / sheetWidth, textureCoordinates.y * height / sheetHeight};
}


Tile Tile::CreateFromCoordinates(Biome biome, uint32 properties, const Vector2& textureCoordinates) {
    return {biome, properties, textureCoordinates};
}
