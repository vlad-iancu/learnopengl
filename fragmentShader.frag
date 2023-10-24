#version 330 core
in vec4 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;
in float Albedo;

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
out vec4 color;

uniform sampler2D Texture;
uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec4 lightColor;

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * ourColor;
    float ambientStrength = 0.2;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec4 specular = Albedo * spec * lightColor;
    color = (lightColor * ambientStrength + diffuse + specular) * texture(Texture, TexCoord) * ourColor;
}

