#include <chicken3421/error.hpp>

#include <chicken3421/file_utils.hpp>

#include <chicken3421/gl_utils.hpp>

namespace chicken3421 {
    GLuint make_shader(const std::string &path, GLenum shader_type) {
        const std::string s_src = read_file(path);

        GLuint shad = glCreateShader(shader_type);
        const char *shader_src = s_src.data();
        glShaderSource(shad, 1, &shader_src, nullptr);
        glCompileShader(shad);

        GLint did_compile;
        glGetShaderiv(shad, GL_COMPILE_STATUS, &did_compile);

        if (!did_compile) {
            // 1024 chars for a log should be enough..........
            std::string log = std::string(1024 + 1, 0);
            glGetShaderInfoLog(shad, 1024 + 1, nullptr, log.data());

            expect(did_compile, log);

            return 0;
        } else {
            return shad;
        }
    }

    void delete_shader(GLuint shader) {
        glDeleteShader(shader);
    }


    GLuint make_program(GLuint vs, GLuint fs) {
        GLuint prog = glCreateProgram();
        glAttachShader(prog, vs);
        glAttachShader(prog, fs);

        glLinkProgram(prog);
        glValidateProgram(prog);

        GLint is_valid;
        glGetProgramiv(prog, GL_VALIDATE_STATUS, &is_valid);

        if (!is_valid) {
            // 1024 chars for a log should be enough..........
            std::string log = std::string(1024 + 1, 0);
            glGetProgramInfoLog(prog, 1024 + 1, nullptr, log.data());

            expect(is_valid, log);

            return 0;
        } else {
            return prog;
        }
    }

    void delete_program(GLuint program) {
        glDeleteProgram(program);
    }

}