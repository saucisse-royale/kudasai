#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "RAII.hpp"
#include "InputStateManager.hpp"
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
		explicit Window(ContextConfig contextConfig);
		~Window();
		void init(WindowConfig const& windowConfig, const std::function<void(const Drawer&)>& renderCallback);
		std::vector<InputStateManager> input();
		void render();

		GLFWwindow* window;
		static void resize_callback(GLFWwindow* window, int width, int height);

	private:
		VulkanContext _vulkanContext;

		std::function<void(const Drawer&)> renderCallback;
		std::vector<InputStateManager> inputs{};
		virtual void drawRectangle(double x, double y, double width, double height) override;
		virtual void drawOval(double x, double y, double width, double height) override;
	};

} // namespace kds

#endif
