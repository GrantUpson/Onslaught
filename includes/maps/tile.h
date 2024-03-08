#ifndef TILE_H
#define TILE_H

#include "types.h"


enum Biome : uint16 {
    Plains = 0,
    Forest = 1
};


struct Tile {
    static constexpr uint8 textureId = 1;
    static constexpr uint8 width = 16;
    static constexpr uint8 height = 16;
    static constexpr uint16 sheetWidth = 640;
    static constexpr uint16 sheetHeight = 368;

    const Biome biome;
    uint32 properties {0};
    Vector2 textureCoordinates[4];

    Tile(Biome biome, uint32 properties, const Vector2& textureCoordinates);
    static Tile CreateFromCoordinates(Biome biome, uint32 properties, const Vector2& textureCoordinates);
};


#endif
