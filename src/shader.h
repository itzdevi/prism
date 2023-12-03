#pragma once

typedef struct Shader {
    unsigned int program;
} Shader;

Shader shaderInit(const char* vertPath, const char* fragPath);
void shaderUse(Shader shader);
void shaderAddFloat(Shader shader, const char* name, float value);
void openFile(const char* path, char* buf);