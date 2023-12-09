#include <glad/glad.h>
#include <iostream>
#include "mesh.h"

Mesh::Mesh(float vertices[], int verticesSize, int indices[], int indicesSize, float texCoords[], int texCoordsSize, float normals[], int normalsSize) {
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    m_vbo = GenerateArrayBuffer(0, 3, GL_FLOAT, sizeof(float) * 3, vertices, verticesSize, GL_STATIC_DRAW);

    glGenBuffers(1, &m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_STATIC_DRAW);

    GenerateArrayBuffer(1, 2, GL_FLOAT, sizeof(float) * 2, texCoords, texCoordsSize, GL_STATIC_DRAW);
    GenerateArrayBuffer(2, 3, GL_FLOAT, sizeof(float) * 3, normals, normalsSize, GL_STATIC_DRAW);

    m_indicesCount = indicesSize / sizeof(indices) * 2;
}

void Mesh::Draw(Shader shader) {
    shader.Use();
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_indicesCount, GL_UNSIGNED_INT, 0);
}

unsigned int Mesh::GenerateArrayBuffer(unsigned int index, int size, unsigned int type, int stride, void* buffer, int bufferSize, unsigned int usage) {
    unsigned int buf;
    glGenBuffers(1, &buf);
    glBindBuffer(GL_ARRAY_BUFFER, buf);
    glBufferData(GL_ARRAY_BUFFER, bufferSize, buffer, usage);

    glVertexAttribPointer(index, size, type, GL_FALSE, stride, (void*)0);
    glEnableVertexAttribArray(index);

    return buf;
}