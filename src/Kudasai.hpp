#pragma once

#include <chrono>
#include "Window.hpp"
#include "Engine.hpp"
#include "InputStateManager.hpp"


typedef std::chrono::nanoseconds::rep time_t;

const time_t TICK_TIME = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::milliseconds{ 10 }).count();

auto start = std::chrono::high_resolution_clock::now();
Window window{};
Engine engine{};
InputStateManager inputStateManager{};
auto closeRequested = false;
time_t accumulator;
float alpha; // for #render(), updated each loop

void initMap();
void initUi();
void init();
void loop();
void render(const Drawer& drawer);
void exit();
void run();
int main();
time_t getNanos();