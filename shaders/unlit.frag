#version 330 core
out vec4 frag;

uniform vec3 u_tint;

void main()
{
    frag = vec4(u_tint, 1.0f);
} 