#ifndef TILE_H
#define TILE_H

#include "types.h"
#include "rendering/sprite.h"


enum PropertyFlags : uint32 {
    Collidable = 1U << 0,
    Swimmable = 1U << 1
};


enum Biome : uint16 {
    Plains = 0,
    Forest = 1
};


class Tile {
public:
    Tile(const uint32 properties, const Biome biome, const Sprite& texture) : properties(properties), biome(biome), texture(texture) {}

    [[nodiscard]] bool IsSet(uint32 property) const;

    void SetProperty(uint32 property);
    void UnsetProperty(uint32 property);

    [[nodiscard]] uint32 GetProperties() const;
    [[nodiscard]] uint16 GetBiome() const;
    [[nodiscard]] const Sprite& GetSprite() const;

private:
    uint32 properties;
    const Biome biome;
    const Sprite texture;
};


#endif
