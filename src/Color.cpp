
#include "Color.hpp"
#include <algorithm>

namespace kds {
Color::Color()
    : r(0)
    , g(0)
    , b(0)
    , a(255)
{
}

Color::Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue)
    : r(red)
    , g(green)
    , b(blue)
    , a(255)
{
}

Color::Color(std::uint8_t red, std::uint8_t green, std::uint8_t blue, std::uint8_t alpha)
    : r(red)
    , g(green)
    , b(blue)
    , a(alpha)
{
}

Color::Color(const std::uint32_t& color)
    : r((color & 0xff000000) >> 24)
    , g((color & 0x00ff0000) >> 16)
    , b((color & 0x0000ff00) >> 8)
    , a((color & 0x000000ff) >> 0)
{
}

std::uint32_t Color::toInteger()
{
    return (r << 24) | (g << 16) | (b << 8) | a;
}

bool Color::operator==(const Color& other) const
{
    return (r == other.r) && (g == other.g) && (b == other.b) && (a == other.a);
}

} // namespace kds
