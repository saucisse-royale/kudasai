#pragma once

#include <chrono>
#include "Window.hpp"
#include "Engine.hpp"
#include "InputStateManager.hpp"

typedef std::chrono::nanoseconds::rep time_t;

class Kudasai {
public:
	void run();
private:
	const time_t TICK_TIME = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds{ 10 }).count();

	std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
	Window window{};
	Engine engine{};
	InputStateManager inputStateManager{};
	bool closeRequested = false;
	time_t accumulator;
	float alpha; // for #render(), updated each loop

	void initMap();
	void initUi();
	void init();
	void loop();
	void render(const Drawer& drawer);
	void exit();

	time_t getNanos();
};

int main();