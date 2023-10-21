#version 330 core
in vec4 ourColor;
in vec2 TexCoord;
in vec3 Normal;
in vec3 FragPos;

out vec4 color;

uniform sampler2D Texture;
uniform vec4 ambient;
uniform vec3 lightPos;


void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * ourColor;
    float ambientStrength = 0.2;
    color = (ambient * ambientStrength + diffuse) * texture(Texture, TexCoord) * ourColor;
}

