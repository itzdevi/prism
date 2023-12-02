#include <shader.h>
#include <glad/glad.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Shader shaderInit(const char* vertPath, const char* fragPath) {
    char* vertSource = (char*)calloc(512, sizeof(char));
    char* fragSource = (char*)calloc(512, sizeof(char));

    openFile(vertPath, vertSource);
    openFile(fragPath, fragSource);

    unsigned int vertShader;
    unsigned int fragShader;
    unsigned int program;

    {
        vertShader = glCreateShader(GL_VERTEX_SHADER);

        glShaderSource(vertShader, 1, &vertSource, NULL);
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

        glShaderSource(fragShader, 1, &fragSource, NULL);
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

void shaderUse(Shader shader) {
    glUseProgram(shader.program);
}

void shaderAddFloat(Shader shader, const char* name, float value) {
    glUniform1f(glGetUniformLocation(shader.program, name), value);
}

void openFile(const char* path, char* buf) {
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