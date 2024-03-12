#ifndef SPRITE_H
#define SPRITE_H

#include "types.h"

struct Sprite {
    Sprite(uint8 textureIndex, Vector2 textureCoordinates, uint8 width, uint8 height);

    const uint8 textureIndex;
    Vector2 textureCoordinates[4];
    const uint8 width;
    const uint8 height;
};


#endif
