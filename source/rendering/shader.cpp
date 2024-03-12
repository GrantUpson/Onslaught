#include "rendering/shader.h"
#include <glad/glad.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "glm/gtc/type_ptr.hpp"


Shader::Shader(const std::string& vertexFilepath, const std::string& fragmentFilepath) {
    std::string vertexCode;
    std::string fragmentCode;

    try {
        std::ifstream vertexShaderFile(vertexFilepath);
        std::ifstream fragmentShaderFile(fragmentFilepath);

        std::stringstream vertexShaderStream;
        std::stringstream fragmentShaderStream;

        vertexShaderStream << vertexShaderFile.rdbuf();
        fragmentShaderStream << fragmentShaderFile.rdbuf();

        vertexShaderFile.close();
        fragmentShaderFile.close();

        vertexCode = vertexShaderStream.str();
        fragmentCode = fragmentShaderStream.str();
    }
    catch (std::exception& e) {
        std::cout << "Error: Failed to read shader files" << e.what() << std::endl;
    }

    const char *vertexShaderCode = vertexCode.c_str();
    const char *fragmentShaderCode = fragmentCode.c_str();

    int success;
    char infoLog[512];

    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderCode, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        //TODO Log rather than print to console
        std::cout << "Error: Vertex Shader Compilation Failed\n" << infoLog << std::endl;
    }

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderCode, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        //TODO Log rather than print to console
        std::cout << "Error: Fragment Shader Compilation Failed\n" << infoLog << std::endl;
    }

    id = glCreateProgram();
    glAttachShader(id, vertexShader);
    glAttachShader(id, fragmentShader);
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &success);

    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, infoLog);
        //TODO Log rather than print to console
        std::cout << "Error: Linking Failed for Shader Program\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}


void Shader::Bind() const {
    glUseProgram(id);
}


uint32 Shader::GetId() const {
    return id;
}


void Shader::SetUniformMatrix4(const std::string& name, const Matrix4& matrix) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE, value_ptr(matrix));
}


Shader::~Shader() {
    glDeleteProgram(id);
}
