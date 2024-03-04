#ifndef TILE_H
#define TILE_H

#include "types.h"


struct Tile {
    uint32 textureId = 0;
    uint32 properties = 0;
    Vector2 textureCoordinates[4];

    Tile(const Vector2& min, const Vector2& max);
    static Tile CreateFromCoordinates(const Vector2& coordinates, const Vector2& size);
};


#endif
