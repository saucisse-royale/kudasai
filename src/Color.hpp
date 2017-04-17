#pragma once

#include <cstdint>
#include <utility>

namespace kds {
struct Color {
    std::uint8_t r;
    std::uint8_t g;
    std::uint8_t b;
    std::uint8_t a;
    Color();
    Color(const std::uint8_t& red, const std::uint8_t& green, const std::uint8_t& blue);
    Color(const std::uint8_t& red, const std::uint8_t& green, const std::uint8_t& blue, const std::uint8_t& alpha);
    Color(const std::uint32_t& color);
    std::uint32_t toInteger();
    bool operator==(const Color& other) const;
};
}
