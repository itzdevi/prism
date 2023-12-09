#include <iostream>
#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"

Shader::Shader(std::string vertPath, std::string fragPath) {
    std::string vertSource = OpenFile(vertPath);
    std::string fragSource = OpenFile(fragPath);

    unsigned int vertShader;
    unsigned int fragShader;

    {
        vertShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertShader, 1, (const char**)&vertSource, NULL);
        glCompileShader(vertShader);

        int success = 0;
        char info[512] = { 0 };
        glGetShaderiv(vertShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vertShader, 512, NULL, info);
            printf("Error at compiling vertex shader: %s\n", info);
        }
    }

    {
        fragShader = glCreateShader(GL_FRAGMENT_SHADER);

        glShaderSource(fragShader, 1, (const char**)&fragSource, NULL);
        glCompileShader(fragShader);

        int success = 0;
        char info[512] = { 0 };
        glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragShader, 512, NULL, info);
            printf("Error at compiling fragment shader: %s\n", info);
        }
    }

    {
        m_program =  glCreateProgram();
        glAttachShader(m_program, vertShader);
        glAttachShader(m_program, fragShader);
        glLinkProgram(m_program);

        int success = 0;
        char info[512] = { 0 };
        glGetProgramiv(m_program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_program, 512, NULL, info);
            printf("Error at linking shader program: %s\n", info);
        }
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);
}

void Shader::Use() {
    glUseProgram(m_program);
}

void Shader::AddFloat(std::string name, float data) {
    glUniform1f(glGetUniformLocation(m_program, name.c_str()), data);
}

void Shader::AddVec3(std::string name, glm::vec3 data) {
    glUniform3fv(glGetUniformLocation(m_program, name.c_str()), 1, glm::value_ptr((data)));
}

void Shader::AddMat4(std::string name, glm::mat4 data) {
    glUniformMatrix4fv(glGetUniformLocation(m_program, name.c_str()), 1, GL_FALSE, glm::value_ptr(data));
}

std::string Shader::OpenFile(std::string path) {
    std::ifstream f(path);

    std::string content;
    std::string line;
    while(std::getline(f, line)) {
        content += line + "\n";
    }

    f.close();

    return content;
}