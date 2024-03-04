#include "maps/tile.h"

Tile::Tile(const Vector2& min, const Vector2& max) {
    textureCoordinates[0] = {min.x, min.y};
    textureCoordinates[1] = {max.x, min.y};
    textureCoordinates[2] = {max.x, max.y};
    textureCoordinates[3] = {min.x, max.y};
}


Tile Tile::CreateFromCoordinates(const Vector2& coordinates, const Vector2& size) {
    constexpr float sheetWidth = 640.0f, sheetHeight = 360;

    Vector2 min = { (coordinates.x * size.x) / sheetWidth, (coordinates.y * size.y) / sheetHeight };
    Vector2 max = { (coordinates.x + 1 * size.x) / sheetWidth, (coordinates.y + 1 * size.y) / sheetHeight };
    return {min, max};
}
