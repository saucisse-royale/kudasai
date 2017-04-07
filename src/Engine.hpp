#pragma once

#include "Window.hpp"

class Engine
{
public:
	Engine();
	~Engine();
	void init();
	void logic(const std::vector<InputStateManager>& inputs);
	void render(const Drawer& drawer, float alpha);
private:
	int level;
	Map map;
	std::vector<
};

struct Map
{
	inline Map(std::size_t width_, std::size_t height_) : width(width_), height(height_), map(width*height) {}
	std::size_t width;
	std::size_t height;
	std::vector<Tile*> map;
	inline Tile** operator[](std::size_t x) { return &map[x*height]; }
};

enum Tile
{
	GROUND_BLACK,
	GROUND_RED,
};