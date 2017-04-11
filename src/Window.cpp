#include "Window.hpp"
#include "VulkanConfig.hpp"
#include "VulkanContext.hpp"


namespace kds {

	Window::Window()
	{
	}


	Window::~Window()
	{
		close();
	}

	// callbacks
	void Window::resize_callback(GLFWwindow *window, int width, int height) {
		return;
	}

	void Window::init(WindowConfig const& windowConfig, const std::function<void(const Drawer&)>& renderCallback)
	{
		ContextConfig contextConfig{};
		contextConfig.debugConfig.enabled = true;
		contextConfig.debugConfig.severity = DebugConfig::FULL;
		contextConfig.deviceQueueConfig.graphicsQueueInfos.count = 16;
		//contextConfig.deviceQueueConfig.computeQueueInfos.count = 15;
		contextConfig.windowConfig = windowConfig;
		init(contextConfig, renderCallback);
	}

	void Window::init(ContextConfig const& contextConfig, const std::function<void(const Drawer&)>& renderCallback)
	{
		this->renderCallback = renderCallback;
		// TODO init opengl and show window
		// TODO notamment register les inputs callbacks et la logique pour les mettre dans inputs
		if (!glfwInit()) {
			std::cerr << "KDS FATAL: failed to init GLFW\n";
			exit(1);
		}

		// Disable openGL
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, contextConfig.windowConfig.resizable ? GLFW_TRUE : GLFW_FALSE);

		window = glfwCreateWindow(contextConfig.windowConfig.width, contextConfig.windowConfig.height, contextConfig.windowConfig.title.c_str(), nullptr, nullptr);

		if (window == nullptr) {
			std::cerr << "KDS FATAL: Failed to create a GLFW window\n";
			exit(1);
		}

		glfwSetWindowUserPointer(window, this);
		glfwSetWindowSizeCallback(window, resize_callback);

		_vulkanContext.create(contextConfig, window);
	}

	void Window::close()
	{
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	std::vector<Input> Window::input()
	{
		// TODO glfwPollEvents
		std::vector<Input>& inputs = this->inputs;
		this->inputs = std::vector<Input>{};
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
