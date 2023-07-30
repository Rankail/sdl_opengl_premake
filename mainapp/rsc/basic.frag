#version 450 core

in vec3 vNormal;
in vec3 vPos;

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightPos;

void main() {

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);

    vec3 norm = normalize(vNormal);
    vec3 lightDir = normalize(lightPos - vPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);

    vec3 result = (ambient + diffuse) * objectColor;

    FragColor = vec4(result, 1.0);
}
