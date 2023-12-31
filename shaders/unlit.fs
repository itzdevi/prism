#version 330 core
out vec4 frag;

uniform vec3 u_tint;
uniform sampler2D u_texture;

in vec2 coords;
in vec3 normals;

void main() {
    frag = texture(u_texture, coords);
} 