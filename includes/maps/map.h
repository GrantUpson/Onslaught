#ifndef MAP_H
#define MAP_H

#include "types.h"
#include <string>

enum class MapLayer : uint8 {
    Base = 0,
    Object = 1,
    Top = 2
};


class Map {
public:
    explicit Map(const std::string& filePath);
    ~Map();

    [[nodiscard]] uint32 GetWidth() const;
    [[nodiscard]] uint32 GetHeight() const;
    [[nodiscard]] uint16 GetTileIndex(Vector2i coordinates, MapLayer layerIndex) const;

    void SetTile(uint16 tile, Vector2i coordinates, MapLayer layerIndex);

private:
    std::string name;
    uint32 width {0};
    uint32 height {0};
    uint16** baseLayer {nullptr};
    uint16** objectLayer {nullptr};
    uint16** topLayer {nullptr};
};


#endif