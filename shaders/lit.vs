#version 330 core
layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec3 vertexNormal;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 globalPos;
out vec3 normal;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(vertexPos, 1.0);
    globalPos = vec3(u_model * vec4(vertexPos, 1.0));
    normal = mat3(transpose(inverse(u_model))) * vertexNormal;
}