#pragma once

#include "Color.hpp"
#include "Input.hpp"
#include "RAII.hpp"
#include "VulkanConfig.hpp"
#include "VulkanContext.hpp"
#include <GLFW/glfw3.h>
#include <cmath>
#include <functional>
#include <vector>

namespace kds {

class Drawer {
public:
    virtual ~Drawer() {}

    virtual std::uint32_t getWidth() = 0;
    virtual std::uint32_t getHeight() = 0;

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

class Window : Drawer {
public:
    Window();
    ~Window();
    void init(ContextConfig const& contextConfig, const std::function<void(Drawer&)>& renderCallback);
    void init(WindowConfig const& windowConfig, const std::function<void(Drawer&)>& renderCallback);
    void close();
    std::vector<Input> input();
    void render();

    GLFWwindow* window;

    virtual void pushTranslate(double x, double y) override;
    virtual void popTranslate() override;
    virtual void drawLineCenter(double x, double y, double length, double angle) override;
    virtual void fillCircleBorder(double x, double y, double radius, double width) override;
    virtual void fillRectangle(double x, double y, double width, double height) override;
    virtual void setColor(Color color) override;
    virtual std::uint32_t getWidth() override;
    virtual std::uint32_t getHeight() override;

private:
    bool closed{ true };
    VulkanContext _vulkanContext;
    std::uint32_t width;
    std::uint32_t height;
    std::function<void(Drawer&)> renderCallback;
    std::vector<Input> inputs{};
};
} // namespace kds
