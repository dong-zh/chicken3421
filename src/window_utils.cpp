#include <optional>
#include <iostream>

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
    bool debug_output_enabled = false;

    // Callback used to display OpenGL errors. Derived from implementation at:
    // https://learnopengl.com/In-Practice/Debugging
    void APIENTRY custom_debug_callback(
            GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei,
            const char *message, const void *) {
        // ignore non-significant error/warning codes
        if(id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

        std::cout << "OpenGL debug message (" << id << "): " <<  message << std::endl;

        switch (source) {
            case 0x8246: std::cout << "Source: API"; break;
            case 0x8247: std::cout << "Source: Window System"; break;
            case 0x8248: std::cout << "Source: Shader Compiler"; break;
            case 0x8249: std::cout << "Source: Third Party"; break;
            case 0x824A: std::cout << "Source: Application"; break;
            case 0x824B: std::cout << "Source: Other"; break;
            default: std::cout << "Source: Unknown"; break;
        } std::cout << "; ";

        switch (type) {
            case 0x824C: std::cout << "Type: Error"; break;
            case 0x824D: std::cout << "Type: Deprecated Behaviour"; break;
            case 0x824E: std::cout << "Type: Undefined Behaviour"; break;
            case 0x824F: std::cout << "Type: Portability"; break;
            case 0x8250: std::cout << "Type: Performance"; break;
            case 0x8268: std::cout << "Type: Marker"; break;
            case 0x8269: std::cout << "Type: Push Group"; break;
            case 0x826A: std::cout << "Type: Pop Group"; break;
            case 0x8251: std::cout << "Type: Other"; break;
            default: std::cout << "Type: Unknown"; break;
        } std::cout << "; ";

        switch (severity) {
            case 0x9146: std::cout << "Severity: high"; break;
            case 0x9147: std::cout << "Severity: medium"; break;
            case 0x9148: std::cout << "Severity: low"; break;
            case 0x826B: std::cout << "Severity: notification"; break;
            default: std::cout << "Severity: unknown"; break;
        } std::cout << std::endl;
    }

    typedef void (APIENTRY *debugproc_t)(GLenum, GLenum, GLuint, GLenum, GLsizei, const GLchar *, const void *);
}

namespace chicken3421 {
    GLFWwindow *make_window(int width, int height, const std::string &title) {
        glfw_interop.emplace();

        if (debug_output_enabled) {
            // load 4.3 and request a debug context if enable_debug_output() called
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
        } else {
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        }

#ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);
#endif

        GLFWwindow *win = glfwCreateWindow(width, height, title.data(), nullptr, nullptr);

        GLint flags;
        glGetIntegerv(GL_CONTEXT_FLAGS, &flags);
        if (flags & 0x00000002) {
            std::cout << "Debug output enabled" << std::endl;
            // This is a bit nasty as we can't use GLAD - the version of GLAD included
            // only supports OpenGL 3.3. fwiw this is what OpenGL looks like if you don't
            // use a loader! haha.
            glEnable(0x92e0); // GL_DEBUG_OUTPUT
            glEnable(0x8242); // GL_DEBUG_OUTPUT_SYNCHRONOUS
            auto glDebugMessageCallback =
                    reinterpret_cast<void (*)(debugproc_t, const void *)>(
                            glfwGetProcAddress("glDebugMessageCallback"));
            auto glDebugMessageControl =
                    reinterpret_cast<void (*)(GLenum, GLenum, GLenum,
                                              GLsizei, const GLuint *, GLboolean)>(
                            glfwGetProcAddress("glDebugMessageControl"));
            glDebugMessageCallback(custom_debug_callback, nullptr);
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
        }

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

    void enable_debug_output() {
        // this flag is used in make_window
        debug_output_enabled = true;
    }
}