#pragma once

#include "Color.hpp"
#include "RAII.hpp"
#include "Input.hpp"
#include "VulkanConfig.hpp"
#include <functional>
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include "VulkanContext.hpp"



namespace kds {

	class Drawer {
	public:
		virtual ~Drawer() {}

		virtual void pushTranslate(double x, double y) = 0;
		virtual void popTranslate() = 0;

		virtual void drawLine(double x1, double y1, double x2, double y2);
		virtual void drawLineCenter(double x, double y, double length, double angle) = 0;

		virtual void fillCircle(double x, double y, double radius);
		virtual void fillCircle(double x, double y, double radius, bool centered);
		virtual void fillCircleBorder(double x, double y, double radius, double width, bool centered);
		virtual void fillCircleBorder(double x, double y, double radius, double width) = 0;

		virtual void fillRectangle(double x, double y, double width, double height, bool centered);
		virtual void fillRectangle(double x, double y, double width, double height) = 0;

		virtual void setColor(Color color) = 0;
	};

	class Window : Drawer
	{
	public:
		Window();
		~Window();
		void init(ContextConfig const& contextConfig, const std::function<void(const Drawer&)>& renderCallback);
		void init(WindowConfig const& windowConfig, const std::function<void(const Drawer&)>& renderCallback);
		void close();
		std::vector<Input> input();
		void render();

		GLFWwindow* window;

	private:
		VulkanContext _vulkanContext;

		std::function<void(const Drawer&)> renderCallback;
		std::vector<Input> inputs{};
        virtual void pushTranslate(double x, double y) override;
        virtual void popTranslate() override;
        virtual void drawLineCenter(double x, double y, double length, double angle) override;
        virtual void fillCircleBorder(double x, double y, double radius, double width) override;
        virtual void fillRectangle(double x, double y, double width, double height) override;
        virtual void setColor(Color color) override;
    };
} // namespace kds
