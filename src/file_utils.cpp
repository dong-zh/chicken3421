#include <fstream>

#include <chicken3421/file_utils.hpp>


namespace chicken3421 {
    std::string read_file(const std::string &path) {
        auto f = std::ifstream(path.data());
        return { std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>() };
    }

}