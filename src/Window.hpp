#pragma once

#include "VulkanContext.hpp"
#include "RAII.hpp"
#include "InputStateManager.hpp"
#include <functional>



class Drawer {
public:
	virtual void drawRectangle(double x, double y, double width, double height) = 0;
	virtual void drawOval(double x, double y, double width, double height) = 0;
	virtual void drawCircle(double x, double y, double radius) {
		drawOval(x, y, radius, radius);
	}
	virtual ~Drawer() {}
};

class Window : Drawer
{
public:
	Window();
	~Window();
	void init(const std::function<void(const Drawer&)>& renderCallback);
	std::vector<InputStateManager> input();
	void render();
	void exit();

private:
	std::function<void(const Drawer&)> renderCallback;
	std::vector<InputStateManager> inputs{};
	virtual void drawRectangle(double x, double y, double width, double height) override;
	virtual void drawOval(double x, double y, double width, double height) override;
};

