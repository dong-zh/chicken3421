#include <fstream>

#include <stb/stb_image.h>

#include <chicken3421/error.hpp>

#include <chicken3421/file_utils.hpp>


namespace chicken3421 {
    std::string read_file(const std::string &path) {
        auto f = std::ifstream(path.data());
        return { std::istreambuf_iterator<char>(f), std::istreambuf_iterator<char>() };
    }

    image_t load_image(const std::string &filename) {
        image_t img; // NOLINT(cppcoreguidelines-pro-type-member-init)
        img.data = stbi_load(filename.data(), &img.width, &img.height, &img.n_channels, 4);

        chicken3421::expect(img.data, "Could not read " + filename);

        return img;
    }

    void delete_image(image_t &img) {
        stbi_image_free(img.data);

        img.data = nullptr;
        img.width = 0;
        img.height = 0;
        img.n_channels = 0;
    }

}