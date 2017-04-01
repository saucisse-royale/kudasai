#include "Window.hpp"



Window::Window()
{
}


Window::~Window()
{
	exit();
}


void Window::init(const std::function<void(const Drawer&)>& renderCallback)
{
	this->renderCallback = renderCallback;
	// TODO init opengl and show window 
	// TODO notamment register les inputs callbacks et la logique pour les mettre dans inputs
	kds::ContextConfig config{};
	config.debugConfig.enabled = true;
	config.debugConfig.severity = kds::DebugConfig::FULL;
	kds::VulkanContext vulkanContext{ config };
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

void Window::exit()
{
	// TODO free
}

void Window::drawRectangle(double x, double y, double width, double height)
{
	// TODO
}

void Window::drawOval(double x, double y, double width, double height)
{
	// TODO
}




