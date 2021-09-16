#include <optional>

#include <chicken3421/error.hpp>

#include <chicken3421/window_utils.hpp>

namespace {
    struct glfw_interop_t {
        glfw_interop_t() {
            glfwInit();
        }

        ~glfw_interop_t() {
            glfwTerminate();
        }
    };
    std::optional<glfw_interop_t> glfw_interop;
}

namespace chicken3421 {
    GLFWwindow *make_window(int width, int height, const std::string &title) {
        glfw_interop.emplace();

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
#endif
        GLFWwindow *win = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

        return win;
    }

    bool make_opengl_context(GLFWwindow *win) {
        glfwMakeContextCurrent(win);
        return gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
    }

    GLFWwindow *make_opengl_window(int width, int height, const std::string &title) {
        GLFWwindow *win = make_window(width, height, title);
        expect(win, "Could not create a new window");

        bool success = make_opengl_context(win);
        expect(success, "Could not load OpenGL");

        return win;
    }
}