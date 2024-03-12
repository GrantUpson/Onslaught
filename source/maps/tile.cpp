#include "maps/tile.h"


bool Tile::IsSet(const uint32 property) const {
    return (properties & property) == property;
}


void Tile::SetProperty(const uint32 property) {
    properties |= property;
}

void Tile::UnsetProperty(const uint32 property) {
    properties &= ~property;
}


uint32 Tile::GetProperties() const {
    return properties;
}


uint16 Tile::GetBiome() const {
    return biome;
}


const Sprite& Tile::GetSprite() const {
    return texture;
}
