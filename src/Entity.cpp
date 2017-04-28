#include "Entity.hpp"
#include <cmath>
#include <limits>

namespace kds {

void Missile::logic()
{
    x = x + dx + ddx / 2;
    y = y + dy + ddy / 2;
    dx = dx + ddx;
    dy = dy + ddy;

    if (x < -100 || x > map->width + 100 || y < -100 || y > map->height + 100) {
        del = true;
        return;
    }
}

void Monster::logic()
{
    double nx = x + dx + ddx / 2;
    double ny = y + dy + ddy / 2;
    int nxFloor = static_cast<int>(std::floor(nx));
    int nyFloor = static_cast<int>(std::floor(ny));
    if (nxFloor < 0) {
        nxFloor = 0;
        nx = 0;
    }
    if (nyFloor < 0) {
        nyFloor = 0;
        ny = 0;
    }
    if (nxFloor >= map->width) {
        nxFloor = map->width - 1;
        nx = map->width - 0.001;
    }
    if (nyFloor >= map->height) {
        nyFloor = map->height - 1;
        ny = map->height - 0.001;
    }
    if (!(*map)[nxFloor][nyFloor]->monsterSolid) {
        x = nx;
        y = ny;
        return;
    }
    if (std::abs(dx) > std::abs(ny)) {
        y = ny;
        std::uint32_t nnx;
        if (dx < 0) {
            for (nnx = nxFloor + 1; (*map)[nnx][nyFloor]->monsterSolid; ++nnx)
                ;
            x = nnx;
            return;
        }
        for (nnx = nxFloor - 1; (*map)[nnx][nyFloor]->monsterSolid; --nnx)
            ;
        x = nnx - 0.001;
        return;
    }
    x = nx;
    std::uint32_t nny;
    if (dy < 0) {
        for (nny = nyFloor + 1; (*map)[nxFloor][nny]->monsterSolid; ++nny)
            ;
        y = nny;
        return;
    }
    for (nny = nyFloor - 1; (*map)[nxFloor][nny]->monsterSolid; --nny)
        ;
    y = nny - 0.001;
    return;
}

bool Monster::onGround()
{
    return y - std::floor(y) < 0.01 && (*map)[static_cast<int>(std::floor(x))][static_cast<int>(std::floor(y))]->monsterSolid;
}
}