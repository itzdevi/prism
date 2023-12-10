#version 330 core

uniform vec3 u_albedo;
uniform vec3 u_lightColor;
uniform vec3 u_lightPosition;
uniform sampler2D u_mainTex;

in vec3 globalPos;
in vec2 texCoord;
in vec3 normal;

void main() {
    float ambientStrength = 0.2;
    vec3 ambient = ambientStrength * u_lightColor * texture2D(u_mainTex, texCoord).xyz;

    vec3 N = normalize(normal);
    vec3 L = normalize(u_lightPosition - globalPos);

    float diff = max(dot(N, L), 0.0);
    vec3 diffuse = diff * u_lightColor;

    vec3 result = (ambient + diffuse) * u_albedo;
    gl_FragColor = vec4(result, 1);
}