#ifndef MAP_H
#define MAP_H

#include "types.h"
#include <string>


enum class MapLayer {
    Base,
    Object,
    Top
};


class Map {
public:
    Map(std::string  name, uint16 const width, uint16 const height, uint16** tiles) : name(std::move(name)), width(width), height(height), baseLayer(tiles) {}
    ~Map();
    static Owner<Map> LoadMap(const std::string& filePath);

    [[nodiscard]] uint32 GetWidth() const;
    [[nodiscard]] uint32 GetHeight() const;
    [[nodiscard]] uint16 GetTileIndex(Vector2i coordinates, MapLayer layerIndex) const;

    void SetTile(uint16 tile, Vector2i coordinates, MapLayer layerIndex);

private:
    const std::string name;
    uint32 width {0};
    uint32 height {0};
    uint16** baseLayer {nullptr};
    uint16** objectLayer {nullptr};
    uint16** topLayer {nullptr};
};


#endif