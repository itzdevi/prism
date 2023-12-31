#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoords;
layout (location = 2) in vec3 normals;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec2 coords;
out vec3 normal;

void main() {
    gl_Position = u_projection * u_view * u_model * vec4(pos, 1.0);
    coords = vec2(texCoords.xy);
    normal = normals;
}
