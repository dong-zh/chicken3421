#ifndef COMP3421_TUTORIALS_FILE_UTILS_HPP
#define COMP3421_TUTORIALS_FILE_UTILS_HPP

#include <string>

namespace chicken3421 {

    /**
     *
     * Reads the file at "path" and returns its contents.
     *
     * Throws an exception if "path" is not accessible.
     *
     * @param path: The path to the file to read.
     * @return The content of the file.
     */
    std::string read_file(const std::string &path);

}

#endif //COMP3421_TUTORIALS_FILE_UTILS_HPP
