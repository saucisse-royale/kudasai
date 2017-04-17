#include "Input.hpp"

namespace kds {

    Input::InputData::InputData(const std::pair<std::size_t, bool>& code_) : code(code_) {
    }

    Input::InputData::InputData(const std::pair<double, double>& move_) : move(move_) {
    }

    Input::InputData::InputData(const std::size_t& scroll_) : scroll(scroll_) {
    }

}