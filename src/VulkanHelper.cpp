#include "VulkanHelper.hpp"

#include <cstdio>

namespace kds {
namespace utils {
	std::vector<char> read_file(std::string const& path) noexcept {
		FILE* file = fopen(path.c_str(), "r");
		if (file == nullptr) {
			std::cerr << "KDS FATAL: Failed to open file path " << path << ".\n";
			exit(1);
		}
		fseek(file, 0, SEEK_END);
		int64_t fileSize{ftell(file)};
		std::vector<char> buffer(fileSize + 1, '\0'); // +1 for trailing \0 ...
		fseek(file, 0, SEEK_SET);
		fread(buffer.data(), sizeof(char), buffer.size(), file);
		fclose(file);
		return buffer;
	}
} // namespace utils
} // namespace kds
