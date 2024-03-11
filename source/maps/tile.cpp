#include "maps/tile.h"


Tile::Tile(const Biome biome, const uint32 properties, const uint16 x, const uint16 y) : biome(biome), properties(properties) {
    //Bottom Left -> Bottom Right -> Top Right -> Top Left
    this->textureCoordinates[0] = {x * width, (y + 1) * height};
    this->textureCoordinates[1] = {(x + 1) * width, (y + 1) * height};
    this->textureCoordinates[2] = {(x + 1) * width, y * height};
    this->textureCoordinates[3] = {x * width, y * height};
}


Tile Tile::CreateFromCoordinates(Biome biome, uint32 properties, const uint16 x, const uint16 y) {
    return {biome, properties, x, y};
}
