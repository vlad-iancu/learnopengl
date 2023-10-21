#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;
layout (location = 2) in vec2 texCoord;
layout (location = 3) in vec3 normal;

out vec4 ourColor;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() { 
	gl_Position = projection * view * model * vec4(position, 1.0f);
    ourColor = color;
    TexCoord = texCoord;
    Normal = normal;
    FragPos = vec3(model * vec4(position, 1.0f));
}
