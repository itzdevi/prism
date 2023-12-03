#include <glad/glad.h>
#include <stdio.h>
#include "mesh.h"

Mesh MeshInit(Shader shader, float vertices[], int verticesSize, int indices[], int indicesSize) {
    unsigned int vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    unsigned int vbo;
    vbo = GenerateArrayBuffer(0, 3, GL_FLOAT, sizeof(float) * 3, vertices, verticesSize, GL_STATIC_DRAW);

    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    Mesh mesh = {.vao = vao, .vbo = vbo, .ebo = ebo, .indicesSize = indicesSize / 4, .shader = shader};
    return mesh;
}

void MeshDraw(Mesh mesh) {
    ShaderUse(mesh.shader);
    glBindVertexArray(mesh.vao);
    glDrawElements(GL_TRIANGLES, mesh.indicesSize, GL_UNSIGNED_INT, 0);
}

unsigned int GenerateArrayBuffer(unsigned int index, int size, unsigned int type, int stride, void* buffer, int bufferSize, unsigned int usage) {
    unsigned int buf;
    glGenBuffers(1, &buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, buffer, usage);

    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(index);

    return (unsigned int)buffer;
}