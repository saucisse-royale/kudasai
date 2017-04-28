#pragma once

#include "Entity.hpp"
#include "Input.hpp"
#include "Map.hpp"
#include "Window.hpp"
#include <array>
#include <vector>

namespace kds {

class Engine {
public:
    Engine();
    ~Engine();
    void init();
    bool logic(const std::vector<Input>& inputs);
    void render(Drawer& drawer, float alpha);

private:
    static const std::uint32_t tileSize{ 15 };
    static const std::uint32_t maxLevels{ 10 };
    void createLevel();
    std::uint32_t level{ 0 };
    Map map;
    std::vector<Missile> missiles{};
    std::vector<Monster> enemies{};
    Monster player{ 0, 0, 0 };
    int playerXState{ 0 };
    bool inputLeft{};
    bool inputRight{};
    bool inputUp{};
};
}