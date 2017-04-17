#include "Window.hpp"
#include "VulkanConfig.hpp"
#include "VulkanContext.hpp"


namespace kds {

    void Drawer::drawLine(double x1, double y1, double x2, double y2) {
        drawLineCenter((x1 + x2) / 2, (y1 + y2) / 2, std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)), std::atan2(y2 - y1, x2 - x1));
    }

	void Drawer::fillCircle(double x, double y, double radius) {
		fillCircle(x, y, radius, true);
	}

	void Drawer::fillCircle(double x, double y, double radius, bool centered) {
		if (centered) {
			fillCircleBorder(x, y, radius, 0);
		} else {
			fillCircleBorder(x + radius / 2, y + radius / 2, radius, 0);
		}
	}

	void Drawer::fillCircleBorder(double x, double y, double radius, double width, bool centered) {
		if (centered) {
			fillCircleBorder(x, y, radius, width);
		} else {
			fillCircleBorder(x + radius / 2, y + radius / 2, radius, width);
		}
	}

	void Drawer::fillRectangle(double x, double y, double width, double height, bool centered) {
		if (centered) {
			fillRectangle(x, y, width, height);
		} else {
			fillRectangle(x + width / 2, y + height / 2, width, height);
		}
	}

	Window::Window()
	{
	}


	Window::~Window()
	{
		close();
	}

	void Window::init(WindowConfig const& windowConfig, const std::function<void(const Drawer&)>& renderCallback)
	{
		ContextConfig contextConfig{};
		contextConfig.debugConfig.enabled = true;
		contextConfig.debugConfig.severity = DebugConfig::FULL;
		contextConfig.deviceQueueConfig.graphicsQueueInfos.count = 1;
		//contextConfig.deviceQueueConfig.computeQueueInfos.count = 15;
		contextConfig.windowConfig = windowConfig;
		init(contextConfig, renderCallback);
	}

	void Window::init(ContextConfig const& contextConfig, const std::function<void(const Drawer&)>& renderCallback)
	{
		this->renderCallback = renderCallback;

        glfwSetErrorCallback([](int error, const char* description){
            std::cerr << "KDS ERROR: GLFW error: " << error << " - " << description << std::endl;
        });

		if (!glfwInit()) {
			std::cerr << "KDS FATAL: failed to init GLFW" << std::endl;
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

		glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height) {

        });

        glfwSetScrollCallback(window, [](GLFWwindow* window, double xoffset, double yoffset) {
            static_cast<Window*>(glfwGetWindowUserPointer(window))->inputs.push_back(Input{Input::SCROLL, std::lround(-yoffset)});
        });
        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
            static_cast<Window*>(glfwGetWindowUserPointer(window))->inputs.push_back(Input{Input::KEY, std::pair<std::size_t, bool>{scancode, action == GLFW_PRESS}});
        });
        glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
            static_cast<Window*>(glfwGetWindowUserPointer(window))->inputs.push_back(Input{Input::MOVE, std::pair<double, double>{xpos, ypos}});
        });
        glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
            static_cast<Window*>(glfwGetWindowUserPointer(window))->inputs.push_back(Input{Input::MOUSE, std::pair<std::size_t, bool>{button, action == GLFW_PRESS}});
        });

		_vulkanContext.create(contextConfig, window);
	}

	void Window::close()
	{
		vkDeviceWaitIdle(_vulkanContext._device);
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	std::vector<Input> Window::input()
	{
		glfwPollEvents();
		std::vector<Input>& inputs = this->inputs;
		this->inputs = std::vector<Input>{};
		return inputs;
	}

	void Window::render()
	{
		renderCallback(*this);
		_vulkanContext._commandManager.draw();
	}

    void Window::pushTranslate(double x, double y) {

    }

    void Window::popTranslate() {

    }

    void Window::drawLineCenter(double x, double y, double length, double angle) {

    }

    void Window::fillCircleBorder(double x, double y, double radius, double width) {

    }

    void Window::fillRectangle(double x, double y, double width, double height) {

    }

    void Window::setColor(Color color) {

    }

} // namespace kds
