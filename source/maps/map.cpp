#include "maps/map.h"


Map::~Map() {
    for(size_t i = 0; i < height; ++i) {
        delete baseLayer[i];
        delete objectLayer[i];
        delete topLayer[i];
    }

    delete[] baseLayer;
    delete[] objectLayer;
    delete[] topLayer;
}


Owner<Map> Map::LoadMap(const std::string& filePath) {
    //TODO Load maps from file
    //TODO Multiple map laters (hashmap for sparse layers?)

    uint16 width = 40;
    uint16 height = 23;

    uint16** tiles = new uint16*[height];

    for(size_t i = 0; i < height; i++) {
        tiles[i] = new uint16[width] {};
    }

    tiles[0][1] = 1;
    tiles[18][23] = 3;
    tiles[5][19] = 2;
    tiles[13][16] = 4;

    return std::make_unique<Map>("Temp Name", width, height, tiles);
}


uint32 Map::GetWidth() const {
    return width;
}


uint32 Map::GetHeight() const {
    return height;
}


uint16 Map::GetTileIndex(const Vector2i coordinates, const MapLayer layerIndex) const {
    switch (layerIndex) {
        case MapLayer::Base: return baseLayer[coordinates.y][coordinates.x];
        case MapLayer::Object: return objectLayer[coordinates.y][coordinates.x];
        case MapLayer::Top: return topLayer[coordinates.y][coordinates.x];
        default: return 0;
    }
}


void Map::SetTile(const uint16 tile, const Vector2i coordinates, const MapLayer layerIndex) {
    switch (layerIndex) {
        case MapLayer::Base: baseLayer[coordinates.y][coordinates.x] = tile;
        case MapLayer::Object: objectLayer[coordinates.y][coordinates.x] = tile;
        case MapLayer::Top: topLayer[coordinates.y][coordinates.x] = tile;
    }
}
