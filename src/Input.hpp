#pragma once

#include <utility>

namespace kds {

struct Input {
    enum InputType { KEY,
        MOUSE,
        MOVE,
        SCROLL };
    InputType type;
    union InputData {
    public:
        std::pair<std::size_t, bool> code;
        std::pair<double, double> move;
        std::size_t scroll;
        InputData(const std::pair<std::size_t, bool>& code_);
        InputData(const std::pair<double, double>& move_);
        InputData(const std::size_t& scroll_);
    };
    InputData data;
};
}
