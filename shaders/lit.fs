#version 330 core

uniform vec3 u_albedo;
uniform vec3 u_lightColor;
uniform vec3 u_lightPosition;

in vec3 globalPos;
in vec3 normal;

void main() {
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * u_lightColor;

    vec3 N = normalize(normal);
    vec3 L = normalize(u_lightPosition - globalPos);

    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = diff * u_lightColor;

    vec3 result = (ambient + diff) * u_albedo;
    gl_FragColor = vec4(result, 1.0);
}