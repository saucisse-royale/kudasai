#include "VulkanHelper.hpp"


namespace kds {
namespace utils {
	std::vector<char> read_file(std::string const& path) noexcept {
        std::ifstream file(path);
        if(!file) {
            std::cerr << "KDS FATAL: Failed to open file path " << path << ".\n";
            exit(1);
        }
        file.seekg(0,std::ios::end);
        std::streampos length = file.tellg();
        file.seekg(0,std::ios::beg);
        std::vector<char> buffer(1+length,'\0');
        file.read(&buffer[0],length);
		return buffer;
	}
} // namespace utils
} // namespace kds
