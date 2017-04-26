#include "Engine.hpp"

namespace kds {
  
  Engine::Engine()
  {
  }
  
  Engine::~Engine()
  {
  }
  
  void Engine::init()
  {
    createLevel();
  }
  
  bool Engine::logic(const std::vector<Input>& inputs)
  {
    for(const Input& input : inputs) {
      switch(input.type) {
        case Input::InputType::KEY:
          if(input.data.code.second) {
            if(input.data.code.first == GLFW_KEY_LEFT) {
              inputLeft = true;
              playerXState = -1;
            } else if(input.data.code.first == GLFW_KEY_RIGHT) {
              inputRight = true;
              playerXState = 1;
            } else if(input.data.code.first == GLFW_KEY_UP) {
              inputUp = true;
            } else if(input.data.code.first == GLFW_KEY_ESCAPE) {
              return true;
            }
          } else {
            if(input.data.code.first == GLFW_KEY_LEFT) {
              inputLeft = false;
              playerXState = inputRight ? 1 : 0;
            } else if(input.data.code.first == GLFW_KEY_RIGHT) {
              inputRight = false;
              playerXState = inputLeft ? -1 : 0;
            } else if(input.data.code.first == GLFW_KEY_UP) {
              inputUp = false;
            }
          }
          break;
        case Input::InputType::MOUSE:
          break;
        case Input::InputType::SCROLL:
          break;
        case Input::InputType::MOVE:
          break;
      }
    }
    if(inputUp && player.onGround())
      player.dy = 1;
    player.dx = playerXState;
    player.logic();
    for(Missile& missile : missiles) {
      missile.logic();
    }
    for(Monster& monster : enemies) {
      monster.logic();
    }
    // TODO collision
    // TODO gagné level
    return false;
  }
  
  void Engine::render(Drawer& drawer, float alpha)
  {
    // TODO render all objects
    std::uint32_t playerX = static_cast<std::uint32_t>(player.x);
    std::uint32_t playerY = static_cast<std::uint32_t>(player.y);
    std::uint32_t playerXOffset = static_cast<std::uint32_t>((player.x - playerX)*tileSize);
    std::uint32_t playerYOffset = static_cast<std::uint32_t>((player.y - playerY)*tileSize);
    std::uint32_t minX = std::max<std::uint32_t>(0, playerX - (drawer.getWidth() / 2) / tileSize - 1);
    std::uint32_t maxX = std::min<std::uint32_t>(map.width - 1, playerX + (drawer.getWidth() / 2) / tileSize + 1);
    std::uint32_t minY = std::max<std::uint32_t>(0, playerY - (drawer.getHeight() / 2) / tileSize - 1);
    std::uint32_t maxY = std::min<std::uint32_t>(map.height - 1, playerY + (drawer.getHeight() / 2) / tileSize + 1);
    Color currentColor = Color{0, 0, 0, 1};
    for(std::uint32_t x = minX; x<=maxX; x++) {
      for(std::uint32_t y = minY; y<=maxY; y++) {
        Tile tile = *map[x][y];
        if(!(currentColor == tile.color)) {
          currentColor = tile.color;
          drawer.setColor(currentColor);
        }
        drawer.fillRectangle(-playerXOffset + (x - playerX) * tileSize + drawer.getWidth() / 2, -playerYOffset + (y - playerY) * tileSize + drawer.getHeight() / 2, tileSize, tileSize, false);
      }
    }
    drawer.setColor(Color{0, 255, 255});
    drawer.fillRectangle(drawer.getWidth() / 2 - tileSize / 2, drawer.getHeight() / 2, tileSize, tileSize, false);
  }
  
  void Engine::createLevel() {
    ++level;
    map = Map{100 + level*20, 50};
    for(std::uint32_t j{0};j<map.width;j++) {
      map[j][0] = &Tile::GROUND_BLACK;
    }
    player.x = 10;
    player.y = 5;
    player.map = &map;
  }
  
}