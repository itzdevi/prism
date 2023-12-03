#pragma once

#include "shader.h"

typedef struct Mesh {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    int indicesSize;
    Shader shader;
} Mesh;

Mesh MeshInit(Shader shader, float vertices[], int verticesSize, int indices[], int indicesSize, float normals[], int normalsSize);
void MeshDraw(Mesh mesh);
unsigned int GenerateArrayBuffer(unsigned int index, int size, unsigned int type, int stride, void* buffer, int bufferSize, unsigned int usage);