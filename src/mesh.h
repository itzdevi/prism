#pragma once

#include <glm/glm.hpp>
#include "shader.h"

class Mesh {
private:
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_ebo;
    unsigned int m_indicesCount;

    unsigned int GenerateArrayBuffer(unsigned int index, int size, unsigned int type, int stride, void* buffer, int bufferSize, unsigned int usage);
public:
    Mesh(float vertices[], int verticesSize, int indices[], int indicesSize, float texCoords[], int texCoordsSize, float normals[], int normalsSize);
    void Draw(Shader shader);
};
