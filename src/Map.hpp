#pragma once

#include "Color.hpp"
#include <vector>

namespace kds {

struct Tile {
    inline Tile(bool monsterSolid_, bool particleSolid_, Color color_)
        : monsterSolid(monsterSolid_)
        , particleSolid(particleSolid_)
        , color(color_)
    {
    }
    const bool monsterSolid;
    const bool particleSolid;
    const Color color;
    static Tile GROUND_BLACK;
    static Tile GROUND_RED;
    static Tile AIR;
};

struct Map {
    Map() = default;
    inline Map(std::size_t width_, std::size_t height_)
        : width(width_)
        , height(height_)
        , map(width * height, &Tile::AIR)
    {
    }
    std::size_t width;
    std::size_t height;
    std::vector<Tile*> map;
    inline Tile** operator[](std::size_t x) { return &map[x * height]; }
};
}
