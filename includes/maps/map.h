#ifndef MAP_H
#define MAP_H

#include "types.h"
#include <string>


class Map {
public:
    Map(std::string  name, uint16 const width, uint16 const height, uint16** tiles) : name(std::move(name)), width(width), height(height), map(tiles) {}
    ~Map();
    static Owner<Map> LoadMap(const std::string& filePath);

    uint32 GetWidth() const;
    uint32 GetHeight() const;
    uint16 GetTile(Vector2i coordinates) const;

    void SetTile(uint16 tile, Vector2i coordinates);

private:
    const std::string name;
    uint32 width {0};
    uint32 height {0};
    uint16** map {nullptr};
};


#endif