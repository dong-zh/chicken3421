#include <chicken3421/error.hpp>

#include <chicken3421/file_utils.hpp>

#include <chicken3421/gl_utils.hpp>

namespace {
    std::string get_program_log(GLuint program) {
        int log_len;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);

        std::string log = std::string(log_len, 0);
        glGetProgramInfoLog(program, log_len, nullptr, log.data());

        return log;
    }

    std::string get_shader_log(GLuint shader) {
        int log_len;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);

        std::string log = std::string(log_len, 0);
        glGetShaderInfoLog(shader, log_len, nullptr, log.data());

        return log;
    }
}

namespace chicken3421 {
    GLuint make_shader(const std::string &path, GLenum shader_type) {
        const std::string s_src = read_file(path);

        GLuint shad = glCreateShader(shader_type);
        const char *shader_src = s_src.data();
        glShaderSource(shad, 1, &shader_src, nullptr);
        glCompileShader(shad);

        GLint did_compile;
        glGetShaderiv(shad, GL_COMPILE_STATUS, &did_compile);

        expect(did_compile, get_shader_log(shad));

        return shad;
    }

    void delete_shader(GLuint shader) {
        glDeleteShader(shader);
    }


    GLuint make_program(GLuint vs, GLuint fs) {
        GLuint prog = glCreateProgram();
        glAttachShader(prog, vs);
        glAttachShader(prog, fs);

        glLinkProgram(prog);
        GLint did_link;
        glGetProgramiv(prog, GL_LINK_STATUS, &did_link);
        expect(did_link, get_program_log(prog));

        //glValidateProgram(prog);
        //GLint is_valid;
        //glGetProgramiv(prog, GL_VALIDATE_STATUS, &is_valid);
        //expect(is_valid, get_program_log(prog));

        return prog;
    }

    void delete_program(GLuint program) {
        glDeleteProgram(program);
    }


    GLuint make_vao() {
        GLuint vao;
        glGenVertexArrays(1, &vao);

        return vao;
    }

    void delete_vao(GLuint vao) {
        glDeleteVertexArrays(1, &vao);
    }

    GLuint make_buffer() {
        GLuint buff;
        glGenBuffers(1, &buff);
        return buff;
    }

    void delete_buffer(GLuint buff) {
        glDeleteBuffers(1, &buff);
    }
}