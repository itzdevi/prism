#pragma once

typedef struct Shader {
    unsigned int program;
} Shader;

Shader shaderInit(const char* vertPath, const char* fragPath);