#include <glad/glad.h>
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <cmath>
#include <forward_list>
#include <algorithm>

#include "render.hpp"
#include "shader.hpp"
#include "Object.hpp"
#include "Texture.hpp"
#include "Camera.hpp"
#include "stb_image.h"

using F21 = float[21];

void clear()
{
    glClearColor(0.2, 0.3, 0.3, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Shader shaders[2];
Camera *camera;

unsigned int woodTexture;
unsigned int faceTexture;

std::forward_list<Texture *> textures;
std::forward_list<Object *> objects;

unsigned int indicesArray[] = {
    // Top face
    0, 1, 2,
    0, 2, 3,
    // Bottom face
    4, 5, 6,
    4, 6, 7,
    // Left face
    8, 9, 10,
    8, 10, 11,
    // Right face
    12, 13, 14,
    12, 14, 15,
    // Front face
    16, 17, 18,
    16, 18, 19,
    // Back face
    20, 21, 22,
    20, 22, 23};

float verticesArray[] =
{
    // Top face
    //x    y    z      r    g    b   a       u    v      nx   ny   nz
    -0.5, 0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 0.0,   0.0, 1.0, 0.0,
    -0.5, 0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 1.0,   0.0, 1.0, 0.0,
     0.5, 0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 1.0,   0.0, 1.0, 0.0,
     0.5, 0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 0.0,   0.0, 1.0, 0.0,
    // Bottom face 
    -0.5,-0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 0.0,   0.0,-1.0, 0.0,
    -0.5,-0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 1.0,   0.0,-1.0, 0.0,
     0.5,-0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 1.0,   0.0,-1.0, 0.0,
     0.5,-0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 0.0,   0.0,-1.0, 0.0,
    // Left face  
    -0.5,-0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 0.0,  -1.0, 0.0, 0.0,
    -0.5, 0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 1.0,  -1.0, 0.0, 0.0,
    -0.5, 0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 1.0,  -1.0, 0.0, 0.0,
    -0.5,-0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 0.0,  -1.0, 0.0, 0.0,
    // Right face   
     0.5,-0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 0.0,   1.0, 0.0, 0.0,
     0.5, 0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 1.0,   1.0, 0.0, 0.0,
     0.5, 0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 1.0,   1.0, 0.0, 0.0,
     0.5,-0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 0.0,   1.0, 0.0, 0.0,
    // Front face   
    -0.5,-0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 0.0,   0.0, 0.0, 1.0,
    -0.5, 0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 1.0,   0.0, 0.0, 1.0,
     0.5, 0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 1.0,   0.0, 0.0, 1.0,
     0.5,-0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 0.0,   0.0, 0.0, 1.0,
    // Back face   
     0.5,-0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 0.0,   0.0, 0.0,-1.0,
     0.5, 0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 1.0,   0.0, 0.0,-1.0,
    -0.5, 0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 1.0,   0.0, 0.0,-1.0,
    -0.5,-0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 0.0,   0.0, 0.0,-1.0
};

float verticesArrayLight[] = {
    // Top face
    // x   y    z      r    g    b    a      u    v      nx   ny   nz
    -0.5, 0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 0.0,   0.0, 1.0, 0.0,
    -0.5, 0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 1.0,   0.0, 1.0, 0.0,
     0.5, 0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 1.0,   0.0, 1.0, 0.0,
     0.5, 0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 0.0,   0.0, 1.0, 0.0,
    // Bottom face  
    -0.5,-0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 0.0,   0.0,-1.0, 0.0,
    -0.5,-0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 1.0,   0.0,-1.0, 0.0,
     0.5,-0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 1.0,   0.0,-1.0, 0.0,
     0.5,-0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 0.0,   0.0,-1.0, 0.0,
    // Left face  
    -0.5,-0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 0.0,  -1.0, 0.0, 0.0,
    -0.5, 0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 1.0,  -1.0, 0.0, 0.0,
    -0.5, 0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 1.0,  -1.0, 0.0, 0.0,
    -0.5,-0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 0.0,  -1.0, 0.0, 0.0,
    // Right face  
     0.5,-0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 0.0,   1.0, 0.0, 0.0,
     0.5, 0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 1.0,   1.0, 0.0, 0.0,
     0.5, 0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 1.0,   1.0, 0.0, 0.0,
     0.5,-0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 0.0,   1.0, 0.0, 0.0,
    // Front face  
    -0.5,-0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 0.0,   0.0, 0.0, 1.0,
    -0.5, 0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 1.0,   0.0, 0.0, 1.0,
     0.5, 0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 1.0,   0.0, 0.0, 1.0,
     0.5,-0.5, 0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 0.0,   0.0, 0.0, 1.0,
    // Back face  
     0.5,-0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 0.0,   0.0, 0.0,-1.0,
     0.5, 0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   0.0, 1.0,   0.0, 0.0,-1.0,
    -0.5, 0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 1.0,   0.0, 0.0,-1.0,
    -0.5,-0.5,-0.5,   1.0, 1.0, 1.0, 1.0,   1.0, 0.0,   0.0, 0.0,-1.0
};
void camera_handler(GLFWwindow *window)
{
    camera->processInput(window);
}

void window_handler(int width, int height)
{
    std::cout << "Window resized to: " << width << "x" << height << std::endl;
    camera->setWidth(width);
    camera->setHeight(height);
    camera->computeTransformations();
}
void init(GLFWwindow *window)
{
    Texture::initBlankTexture();
    Shader shader = Shader("./vertexShader.vert", "./fragmentShader.frag");
    Shader lightShader = Shader("./lightVertexShader.vert", "./lightFragmentShader.frag");
    shaders[0] = shader;
    shaders[1] = lightShader;
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), 90.0f, 0.0, 5.0, width, height, shaders, 2);
    std::cout << "Created camera" << std::endl;
    Texture *woodTexture = new Texture("./container.jpg");
    textures.push_front(woodTexture);
    // create a verticies array that creates a cube centered in 0.0 with a side length of one

    unsigned int verticesSize = sizeof(verticesArray) / sizeof(float);
    unsigned int indicesSize = sizeof(indicesArray) / sizeof(unsigned int);

    // Verifica indicii de la cub si continua
    // Now create the indices array for all six faces of the cube

    glm::mat4 model = glm::mat4(1.0f);
    Object *cube = new Object(
        verticesArray,
        indicesArray,
        verticesSize,
        indicesSize,
        woodTexture,
        &shaders[0],
        model);
    objects.push_front(cube);

    glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);
    model = glm::translate(model, lightPos);
    model = glm::scale(model, glm::vec3(0.2f));
    
    Object *light = new Object(
        verticesArrayLight,
        indicesArray,
        verticesSize,
        indicesSize,
        woodTexture,
        &shaders[1],
        model);
    objects.push_front(light);

    shader.use();
    glUniform4fv(glGetUniformLocation(shader.ID, "ambient"), 1, glm::value_ptr(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
    glUniform3fv(glGetUniformLocation(shader.ID, "lightPos"), 1, glm::value_ptr(lightPos));
    // std::cout << "Created cube" << std::endl;

    // shader->use();
    //  unsigned int transformLoc = glGetUniformLocation(shader->ID, "model");
    //  unsigned int projectionLoc = glGetUniformLocation(shader->ID, "projection");
    //  std::cout << "Transform location: " << transformLoc << std::endl;
    //   Set the transformation matrices transform, view and projection to their corresponding uniform locations in the shader
    //  glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
    //  projection = glm::perspective(45.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    //  glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}
void render(GLFWwindow *window)
{
    clear();
    for (auto object : objects)
    {
        object->render();
    }
}
