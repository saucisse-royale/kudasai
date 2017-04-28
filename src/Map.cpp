#include "Map.hpp"

namespace kds {

Tile Tile::GROUND_BLACK{ true, true, Color{ 0, 0, 0 } };
Tile Tile::GROUND_RED{ true, true, Color{ 255, 0, 0 } };
Tile Tile::AIR{ false, false, Color{ 255, 255, 255, 0 } };
}