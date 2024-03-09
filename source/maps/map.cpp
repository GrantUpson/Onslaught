#include "maps/map.h"


Map::~Map() {
    for(size_t i = 0; i < height; ++i) {
        delete map[i];
    }

    delete[] map;
}


Scope<Map> Map::LoadMap(const std::string& filePath) {
    //TODO Load maps from file

    uint16 width = 40;
    uint16 height = 23;

    uint16** tiles = new uint16*[height];

    for(size_t i = 0; i < height; i++) {
        tiles[i] = new uint16[width] {};
    }

    tiles[0][1] = 1;
    tiles[18][23] = 3;
    tiles[5][19] = 2;

    return std::make_unique<Map>("Temp Name", width, height, tiles);
}


uint32 Map::GetWidth() const {
    return width;
}


uint32 Map::GetHeight() const {
    return height;
}


uint16 Map::GetTile(const Vector2i coordinates) const {
    return map[coordinates.y][coordinates.x];
}


void Map::SetTile(const uint16 tile, const Vector2i coordinates) {
    map[coordinates.y][coordinates.x] = tile;
}
