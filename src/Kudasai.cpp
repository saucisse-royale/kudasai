#include <GLFW/glfw3.h>

#include "Kudasai.hpp"
#include <thread>
#include <iostream>

namespace kds {

void Kudasai::initMap() {
	engine.init();
}

void Kudasai::initUi() {
	WindowConfig config{};
	window.init(config, std::bind(&Kudasai::render, this, std::placeholders::_1));
}

void Kudasai::init() {
	initMap();
	initUi();
}

void Kudasai::loop() {
	time_t lastFrame = getNanos();
	accumulator = 0;
	while (true) {
		time_t newTime = getNanos();
		time_t deltaTime = newTime - lastFrame;
		lastFrame = newTime;
		accumulator += deltaTime;
		while (accumulator >= TICK_TIME) {
			if(engine.logic(window.input()))
        return;
      if(glfwWindowShouldClose(window.window))
        return;
			accumulator -= TICK_TIME;
		}
		alpha = (float) accumulator / TICK_TIME; // update alpha for #render()
		window.render(); // calls render
	}
}

void Kudasai::render(Drawer& drawer) {
	engine.render(drawer, alpha);
}

void Kudasai::close() {
	window.close();
}

void Kudasai::run() {
	init();
	loop();
	close();
}

time_t Kudasai::getNanos() {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
}

}

int main() {
	kds::Kudasai kudasai{};
	kudasai.run();
}
