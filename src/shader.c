#include <shader.h>
#include <glad/glad.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Shader ShaderInit(const char* vertPath, const char* fragPath) {
    char* vertSource = (char*)calloc(2048, sizeof(char));
    char* fragSource = (char*)calloc(2048, sizeof(char));

    OpenFile(vertPath, vertSource);
    OpenFile(fragPath, fragSource);

    unsigned int vertShader;
    unsigned int fragShader;
    unsigned int program;

    {
        vertShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertShader, 1, (const char**)&vertSource, NULL);
        glCompileShader(vertShader);

        int success = 0;
        char info[512] = {};
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
        char info[512] = {};
        glGetShaderiv(fragShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fragShader, 512, NULL, info);
            printf("Error at compiling fragment shader: %s\n", info);
        }
    }

    {
        program =  glCreateProgram();
        glAttachShader(program, vertShader);
        glAttachShader(program, fragShader);
        glLinkProgram(program);

        int success = 0;
        char info[512] = {};
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(program, 512, NULL, info);
            printf("Error at linking shader program: %s\n", info);
        }
    }

    glDeleteShader(vertShader);
    glDeleteShader(fragShader);

    free(vertSource);
    free(fragSource);

    Shader shader;
    shader.program = program;
    return shader;
}

void ShaderUse(Shader shader) {
    glUseProgram(shader.program);
}

void ShaderAddFloat(Shader shader, const char* name, float value) {
    glUniform1f(glGetUniformLocation(shader.program, name), value);
}

void ShaderAddVec3(Shader shader, const char* name, vec3 vector) {
    glUniform3fv(glGetUniformLocation(shader.program, name), 1, vector);
}

void ShaderAddMat4(Shader shader, const char* name, mat4 matrix) {
    glUniformMatrix4fv(glGetUniformLocation(shader.program, name), 1, GL_FALSE, matrix);
}

void OpenFile(const char* path, char* buf) {
    FILE *fp;
    fp = fopen(path, "r");
    char c;
    while (1) {
        c = fgetc(fp);
        if (c == EOF) break;
        int len = strlen(buf);
        buf[len] = c;
    }
    fclose(fp);
}