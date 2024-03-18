#include "maps/map.h"
#include <iostream>
#include <fstream>


Map::Map(const std::string& filePath) {
    //TODO Load maps from file
    //TODO Change sparse map layers to use a sparse array for more efficient memory usage?

    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        //TODO Log to file
        exit(-1);
    }

    int numLayers;
    file >> height >> width >> numLayers; // Read the map dimensions and number of layers

    baseLayer = new uint16*[height];
    objectLayer = new uint16*[height];
    topLayer = new uint16*[height];

    for(size_t i = 0; i < height; i++) {
        baseLayer[i] = new uint16[width] {103};
        objectLayer[i] = new uint16[width] {};
        topLayer[i] = new uint16[width] {};
    }

    // Base Layer
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (file.eof()) {
                std::cerr << "Unexpected end of file while reading map data." << std::endl;
                exit(-3);
            }
            file >> baseLayer[i][j];
            if (file.peek() == ',') file.ignore(); // Skip commas
        }
    }

    // Object Layer
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (file.eof()) {
                std::cerr << "Unexpected end of file while reading map data." << std::endl;
                exit(-3);
            }
            file >> objectLayer[i][j];
            if (file.peek() == ',') file.ignore(); // Skip commas
        }
    }

    // Top Layer
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (file.eof()) {
                std::cerr << "Unexpected end of file while reading map data." << std::endl;
                exit(-3);
            }
            file >> topLayer[i][j];
            if (file.peek() == ',') file.ignore(); // Skip commas
        }
    }

    file.close();


    // width = 40;
    // height = 23;
    //

    //

    //
    // //test init base with grass
    // for(size_t y = 0; y < height; y++) {
    //     for(size_t x = 0; x < width; x++) {
    //         baseLayer[y][x] = 103;
    //     }
    // }

}


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


/**
 * Note: The map origin is the top left corner with the Y axis going down.
 * @param tile The Tile ID to set from the Tiles vector.
 * @param coordinates The X and Y coordinate of the map to modify.
 * @param layerIndex The map layer to modify.
 */
void Map::SetTile(const uint16 tile, const Vector2i coordinates, const MapLayer layerIndex) {
    switch (layerIndex) {
        case MapLayer::Base: baseLayer[coordinates.y][coordinates.x] = tile;
        case MapLayer::Object: objectLayer[coordinates.y][coordinates.x] = tile;
        case MapLayer::Top: topLayer[coordinates.y][coordinates.x] = tile;
    }
}
