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
};

