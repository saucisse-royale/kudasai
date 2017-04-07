#include "Window.hpp"
#include "VulkanConfig.hpp"
#include "VulkanContext.hpp"


namespace kds {
	Window::Window(ContextConfig contextConfig)
	{
		init(contextConfig.windowConfig, {});
		_vulkanContext.create(contextConfig, window);
	}


	Window::~Window()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	// callbacks
	void Window::resize_callback(GLFWwindow *window, int width, int height) {
		return;
	}


	void Window::init(WindowConfig const& windowConfig, const std::function<void(const Drawer&)>& renderCallback)
	{
		this->renderCallback = renderCallback;
		// TODO init opengl and show window
		// TODO notamment register les inputs callbacks et la logique pour les mettre dans inputs
		if (!glfwInit()) {
			std::cerr << "KDS_FATAL: failed to init GLFW\n";
			exit(1);
		}

		// Disable openGL
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, windowConfig.resizable ? GLFW_TRUE : GLFW_FALSE);

		window = glfwCreateWindow(windowConfig.width, windowConfig.height, windowConfig.title.c_str(), nullptr, nullptr);

		if (window == nullptr) {
			std::cerr << "KDS FATAL: Failed to create a GLFW window\n";
			exit(1);
		}

		glfwSetWindowUserPointer(window, this);
		glfwSetWindowSizeCallback(window, resize_callback);
	}

	std::vector<InputStateManager> Window::input()
	{
		// TODO glfwPollEvents
		std::vector<InputStateManager>& inputs = this->inputs;
		this->inputs = std::vector<InputStateManager>{};
		return inputs;
	}

	void Window::render()
	{
		renderCallback(*this);
	}

	void Window::drawRectangle(double x, double y, double width, double height)
	{
		// TODO
	}

	void Window::drawOval(double x, double y, double width, double height)
	{
		// TODO
	}
} // namespace kds
