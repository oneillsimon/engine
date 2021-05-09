//
// Created by simon on 06/05/2021.
//

#include <filesystem>
#include <iostream>

#include <gtest/gtest.h>

#include <rendering/glfw_window.h>
#include <rendering/glsl_program.h>

TEST(glsl_program, constructor) {
    auto program = GLSLProgram();
    ASSERT_FALSE(program.is_linked()); // Assert program is not linked.
    ASSERT_EQ(program.get_handle(), 0); // Assert program has not been given OpenGL handle.
}

TEST(glsl_program, destructor) {
    const auto shader_name = "shader.vert.glsl";
    auto vert_shader = ""
                  "#version 430 core\n"
                  "void main() {\n"
                  "  gl_Position = vec4(1.0, 1.0, 1.0, 1.0);\n"
                  "}\n"
                  "";
    std::ofstream shader_file(shader_name);
    shader_file << vert_shader;
    shader_file.close();

    auto window = GlfwWindow("test", 800, 600);

    auto program = new GLSLProgram();
    program->compile_shader(shader_name, GLSLShaderType::VERTEX);

    ASSERT_FALSE(program->get_handle() == 0);

    auto program_handle = program->get_handle();
    // Query the number of attached shaders.
    GLint num_shaders = 0;
    glGetProgramiv(program_handle, GL_ATTACHED_SHADERS, &num_shaders);
    ASSERT_EQ(num_shaders, 1);

    delete program;

    num_shaders = -1;
    glGetProgramiv(program_handle, GL_ATTACHED_SHADERS, &num_shaders);
    // Number of shader's shouldn't be updated since the program's handle is on longer valid.
    ASSERT_EQ(num_shaders, -1);

    remove(shader_name);
}

TEST(glsl_program, compile_shader) {
    const auto shader_name = "shader.vert.glsl";
    auto vert_shader = ""
                       "#version 430 core\n"
                       "void main() {\n"
                       "  gl_Position = vec4(1.0, 1.0, 1.0, 1.0);\n"
                       "}\n"
                       "";
    std::ofstream shader_file(shader_name);
    shader_file << vert_shader;
    shader_file.close();

    auto window = GlfwWindow("test", 800, 600);

    auto program = GLSLProgram();
    program.compile_shader(shader_name, GLSLShaderType::VERTEX);

    GLint num_shaders = 0;
    glGetProgramiv(program.get_handle(), GL_ATTACHED_SHADERS, &num_shaders);
    ASSERT_EQ(num_shaders, 1);

    remove(shader_name);
}

TEST(glsl_program, compile_shader_file_not_found) {
    const std::string shader_name = "does_not_exist.vert.glsl";

    auto program = GLSLProgram();

    EXPECT_THROW({
        try {
            program.compile_shader(shader_name, GLSLShaderType::VERTEX);
        } catch (const GLSLException& e) {
            EXPECT_STREQ(e.what(), std::string("Shader: " + shader_name + "not found.").c_str());
            throw;
        }
    }, GLSLException);
}

TEST(glsl_program, compile_shader_shader_compilation_error) {
    const auto shader_name = "shader.vert.glsl";
    auto vert_shader = ""
                       "#version 430 core\n"
                       "void main() \n" // Omitt the opening `{` to cause compilation failure.
                       "  gl_Position = vec4(1.0, 1.0, 1.0, 1.0);\n"
                       "}\n"
                       "";
    std::ofstream shader_file(shader_name);
    shader_file << vert_shader;
    shader_file.close();

    auto window = GlfwWindow("test", 800, 600);

    auto program = GLSLProgram();

    EXPECT_THROW({
        try {
            program.compile_shader(shader_name, GLSLShaderType::VERTEX);
        } catch (const GLSLException& e) {
            EXPECT_TRUE(std::string(e.what()).find("syntax error") != std::string::npos);
            throw;
        }
    }, GLSLException);
    remove(shader_name);
}

TEST(glsl_program, compile_shader_unable_to_read_file) {
    std::string shader_name = "shader.vert.glsl";
    auto vert_shader = ""
                       "#version 430 core\n"
                       "void main() {\n"
                       "  gl_Position = vec4(1.0, 1.0, 1.0, 1.0);\n"
                       "}\n"
                       "";
    std::ofstream shader_file(shader_name);
    shader_file << vert_shader;
    shader_file.close();

    // Make file write only, that is to say unreadable.
    std::filesystem::permissions(shader_name, std::filesystem::perms::owner_write);

    auto window = GlfwWindow("test", 800, 600);

    auto program = GLSLProgram();

    EXPECT_THROW({
        try {
            program.compile_shader(shader_name, GLSLShaderType::VERTEX);
        } catch (const GLSLException& e) {
            EXPECT_STREQ(e.what(), std::string("Unable to open: " + shader_name + ".").c_str());
            throw;
        }
    }, GLSLException);
    remove(shader_name.c_str());
}

TEST(glsl_program, link) {
    const auto shader_name = "shader.vert.glsl";
    auto vert_shader = ""
                       "#version 430 core\n"
                       "void main() {\n"
                       "  gl_Position = vec4(1.0, 1.0, 1.0, 1.0);\n"
                       "}\n"
                       "";
    std::ofstream shader_file(shader_name);
    shader_file << vert_shader;
    shader_file.close();

    auto window = GlfwWindow("test", 800, 600);

    auto program = GLSLProgram();
    program.compile_shader(shader_name, GLSLShaderType::VERTEX);

    ASSERT_FALSE(program.is_linked());
    program.link();
    ASSERT_TRUE(program.is_linked());

    remove(shader_name);
}

TEST(glsl_program, link_without_compiling) {
    auto program = GLSLProgram();

    ASSERT_FALSE(program.is_linked());

    EXPECT_THROW({
        try {
            program.link();
        } catch (const GLSLException& e) {
            EXPECT_STREQ(e.what(), "Program has not been compiled");
            throw;
        }
    }, GLSLException);
}

TEST(glsl_program, link_failure) {
    const auto shader_name = "shader.vert.glsl";
    auto vert_shader = ""
                       "#version 430 core\n"
                       "void main() {\n"
                       "  gl_Position = vec4(1.0, 1.0, 1.0, 1.0);\n"
                       "}\n"
                       "";
    std::ofstream shader_file(shader_name);
    shader_file << vert_shader;
    shader_file.close();

    auto window = GlfwWindow("test", 800, 600);

    auto program = GLSLProgram();

    // Compiling GEOMETRY shader with VERTEX shader will cause linker failure.
    program.compile_shader(shader_name, GLSLShaderType::GEOMETRY);

    ASSERT_FALSE(program.is_linked());

    EXPECT_THROW({
        try {
            program.link();
        } catch (const GLSLException& e) {
            EXPECT_TRUE(std::string(e.what()).find("Program link failed.") != std::string::npos);
            throw;
        }
    }, GLSLException);

    remove(shader_name);
}

TEST(glsl_program, use) {
    const auto shader_name = "shader.vert.glsl";
    auto vert_shader = ""
                       "#version 430 core\n"
                       "void main() {\n"
                       "  gl_Position = vec4(1.0, 1.0, 1.0, 1.0);\n"
                       "}\n"
                       "";
    std::ofstream shader_file(shader_name);
    shader_file << vert_shader;
    shader_file.close();

    auto window = GlfwWindow("test", 800, 600);

    auto program = GLSLProgram();

    program.compile_shader(shader_name, GLSLShaderType::VERTEX);
    program.link();

    EXPECT_NO_THROW(program.use());
}

TEST(glsl_program, use_before_link) {
    const auto shader_name = "shader.vert.glsl";
    auto vert_shader = ""
                       "#version 430 core\n"
                       "void main() {\n"
                       "  gl_Position = vec4(1.0, 1.0, 1.0, 1.0);\n"
                       "}\n"
                       "";
    std::ofstream shader_file(shader_name);
    shader_file << vert_shader;
    shader_file.close();

    auto window = GlfwWindow("test", 800, 600);

    auto program = GLSLProgram();

    program.compile_shader(shader_name, GLSLShaderType::VERTEX);

    EXPECT_THROW({
        try{
            program.use();
        } catch (const GLSLException& e) {
            EXPECT_STREQ(e.what(), "Program has not been linked.");
            throw;
        }
    }, GLSLException);

    program.link();
    EXPECT_NO_THROW(program.use());
}