#include "Kudasai.hpp"


void initMap() {

}

void initUi() {
	window.init(render);
}

void init() {
	initMap();
	initUi();
}

void loop() {
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

void render(const Drawer& drawer) {
	// TODO, use alpha for interpolation
}

void exit() {
	window.exit();
}


void run() {
	init();
	loop();
	exit();
}


int main() {
	run();
	return EXIT_SUCCESS;
}

time_t getNanos() {
	return std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::high_resolution_clock::now() - start).count();
}