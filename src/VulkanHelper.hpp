#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "VulkanLoader.hpp"

// A set of helpful macros/functions to shorten the code

#define KDS_CHECK_RESULT(result, msg)\
	if (result != VK_SUCCESS) {\
		std::cerr << "KDS FATAL: " << msg << " Exit code: " << result <<'\n';\
		exit(result);\
	}

namespace kds {
namespace utils {
	std::vector<char> read_file(std::string const& path) noexcept;
} // namespace utils
} // namespace kds
