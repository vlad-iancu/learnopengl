#include <glad/glad.h>
#include "render.hpp"
#include "shader.hpp"
#include <GL/gl.h>
#include <iostream>
#include <cmath>
#include <algorithm>

using F21 = float[21];

void clear()
{
	glClearColor(0.2, 0.3, 0.3, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}
static const GLchar* vertexShaderSource =
    "#version 330 core\n"
    "layout (location = 0) in vec3 position;\n"
    "layout (location = 1) in vec4 color;\n"
    "out vec4 ourColor;\n"
    "void main() {\n"
    "    gl_Position = vec4(position, 1.0f);\n"
    "    ourColor = color;\n"
    "}\n";
static const GLchar* fragmentShaderSource =
    "#version 330 core\n"
    "uniform vec4 ourColor;\n"
    "out vec4 color;\n"
    "void main() {\n"
    "    color = ourColor;\n"
    "}\n";

/*
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;
*/

Shader shader;

unsigned int vaos[2];
unsigned int vbos[2];
unsigned int ebos[2];

float triangle1[21];
float triangle2[21];

unsigned int indices[6]; //We'll use the same indices for both triangles

void init()
{
        shader = Shader("./vertexShader.vert", "./fragmentShader.frag");
        float t1[21] = {
                -0.5, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
                -0.25, 0.5, 0.0, 1.0, 0.0, 0.0, 1.0,
                0.0, 0.0, 0.0, 1.0, 0.0, 0.0, 1.0,
        };
        std::copy_n( 
        t1,
        21,
        triangle1
        );
        float t2[21] = {
                0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0,
                0.25, 0.5, 0.0, 0.0, 1.0, 1.0, 1.0,
                0.5, 0.0, 0.0, 0.0, 1.0, 1.0, 1.0
        };

        unsigned int idx[] = {
                0, 1, 2
        };

        std::copy_n(idx, 3, indices);

        std::copy_n(
        t2,
        21,
        triangle2);

        glGenVertexArrays(2, vaos);
        glGenBuffers(2, vbos);
        glGenBuffers(2, ebos);

        glBindVertexArray(vaos[0]);
        glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 21, triangle1, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[0]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3, indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(vaos[1]);
        glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 21, triangle2, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[1]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3, indices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);
}
void render(GLFWwindow *window)
{
		clear();
/* Build and compile shader program. */
        /* Vertex shader */
        float timeValue = glfwGetTime() / 2;
        std::cout << timeValue << std::endl;
        float greenValue = (std::sin(timeValue) / 2.0f) + 0.5f;
        float redValue = (std::sin(timeValue - M_PI / 2) / 2.0f) + 0.5f;
        float blueValue = (std::sin(timeValue - M_PI / 2) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shader.ID, "ourColor");

        shader.use();
        glUniform4f(vertexColorLocation, redValue, greenValue, blueValue, 1.0f);

        shader.use();
        glBindVertexArray(vaos[0]);
        //glDrawArrays(GL_LINE_LOOP, 0, 3);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

        shader.use();
        glBindVertexArray(vaos[1]);
        //glDrawArrays(GL_LINE_LOOP, 0, 3);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
	
}
