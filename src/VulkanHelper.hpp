#ifndef VULKAN_HELPER_HPP
#define VULKAN_HELPER_HPP

#include <iostream>

#include "VulkanLoader.hpp"

// A set of helpful macros/functions to shorten the code

#define KDS_CHECK_RESULT(result, msg)\
	if (result != VK_SUCCESS) {\
		std::cerr << "KDS FATAL: " << msg << " Exit code: " << result <<'\n';\
		exit(result);\
	}

#endif // VulkanHelper.hpp
