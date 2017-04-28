#pragma once

#include "Map.hpp"

namespace kds {

struct Entity {
    inline Entity(Map* map_, double x_, double y_)
        : map(map_)
        , x(x_)
        , y(y_)
    {
    }

    Map* map;
    double x{};
    double y{};
    double dx{};
    double dy{};
    double ddx{};
    double ddy{};

    bool del{};

    virtual void logic() = 0;
};

struct Missile : Entity {
    inline Missile(Map* map_, double x_, double y_, bool enemy_)
        : Entity(map_, x_, y_)
        , enemy(enemy_)
    {
    }

    bool enemy;

    virtual void logic() override;
};

struct Monster : Entity {
    inline Monster(Map* map_, double x_, double y_)
        : Entity(map_, x_, y_)
    {
    }

    virtual void logic() override;

    bool onGround();
};
}
