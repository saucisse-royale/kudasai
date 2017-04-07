#include "Kudasai.hpp"


void Kudasai::initMap() {
	engine.init();
}

void Kudasai::initUi() {
	window.init(render);
}

void Kudasai::init() {
	initMap();
	initUi();
}

void Kudasai::loop() {
	time_t lastFrame = getNanos();
	accumulator = 0;
	while (!closeRequested) {
		time_t newTime = getNanos();
		time_t deltaTime = newTime - lastFrame;
		lastFrame = newTime;
		accumulator += deltaTime;
		while (accumulator >= TICK_TIME) {
			engine.logic(window.input());
			accumulator -= TICK_TIME;
		}
		alpha = (float) accumulator / TICK_TIME; // update alpha for #render()
		window.render(); // calls render
	}
}

void Kudasai::render(const Drawer& drawer) {
	engine.render(drawer, alpha);
}

void Kudasai::exit() {
	window.exit();
}

void Kudasai::run() {
	init();
	loop();
	exit();
}

time_t Kudasai::getNanos() {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
}

int main() {
	Kudasai kudasai{};
	kudasai.run();
	return EXIT_SUCCESS;
}