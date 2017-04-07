#pragma once

#include "RAII.hpp"
#include "Input.hpp"
#include "VulkanConfig.hpp"
#include <functional>
#include <GLFW/glfw3.h>
#include <vector>
#include "VulkanContext.hpp"



namespace kds {

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
		void init(ContextConfig const& contextConfig, const std::function<void(const Drawer&)>& renderCallback);
		void init(WindowConfig const& windowConfig, const std::function<void(const Drawer&)>& renderCallback);
		void close();
		std::vector<Input> input();
		void render();

		GLFWwindow* window;
		static void resize_callback(GLFWwindow* window, int width, int height);

	private:
		VulkanContext _vulkanContext;

		std::function<void(const Drawer&)> renderCallback;
		std::vector<Input> inputs{};
		virtual void drawRectangle(double x, double y, double width, double height) override;
		virtual void drawOval(double x, double y, double width, double height) override;
	};

} // namespace kds
