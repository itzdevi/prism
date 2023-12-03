#pragma once

#include <cglm/cglm.h>

typedef struct Shader {
    unsigned int program;
} Shader;

Shader ShaderInit(const char* vertPath, const char* fragPath);
void ShaderUse(Shader shader);
void ShaderAddFloat(Shader shader, const char* name, float value);
void ShaderAddColor(Shader shader, const char* name, float r, float g, float b);
void ShaderAddMat4(Shader shader, const char* name, mat4 matrix);
void OpenFile(const char* path, char* buf);