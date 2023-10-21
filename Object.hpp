// Create header guards
#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/gl.h>

#include "Texture.hpp"
#include "shader.hpp"
/*A class that represents a generic opengl object, it has a Vertex Array Object (VAO), a Vertex Buffer Object (VBO),
 an Element Buffer Object (EBO), a Shader Program (SP) and a render function */

// The vertices object should be a struct that contains the 3D coordinates of the vertex, the color of the vertex in RGBA format and the texture coordinates of the vertex
struct vertex
{
    // The x coordinate of the vertex
    float x;
    // The y coordinate of the vertex
    float y;
    // The z coordinate of the vertex
    float z;
    // The red value of the vertex
    float r;
    // The green value of the vertex
    float g;
    // The blue value of the vertex
    float b;
    // The alpha value of the vertex
    float a;
    // The u coordinate of the vertex
    float u;
    // The v coordinate of the vertex
    float v;
    // The x component of the normal vector of the vertex
    float nx;
    // The y component of the normal vector of the vertex
    float ny;
    // The z component of the normal vector of the vertex
};

class Object
{
public:
    // The VAO, VBO, EBO and SP are all unsigned integers
    unsigned int VAO, VBO, EBO;
    // The shader program is a Shader object
    Shader *shader;
    // The vertices, indices and texture are all unsigned integers
    unsigned int vertices, indices;
    // The texture is a Texture object
    Texture *texture;
    // The transform matrix is a GLM mat4 object
    glm::mat4 transform;
    // The vertices array is a float array
    float *verticesArray;
    // The indices array is an unsigned int array
    unsigned int *indicesArray;
    // The size of the vertices array
    unsigned int verticesSize;
    // The size of the indices array
    unsigned int indicesSize;
    // The size of the vertices array in bytes
    unsigned int verticesSizeBytes;
    // The size of the indices array in bytes
    unsigned int indicesSizeBytes;

    void render();

    // Generate a constructor for the object that takes as input an array of vertices, an array of indices, the size of the vertices array and the size of the indices array
    Object(
        float *verticesArray,
        unsigned int *indicesArray,
        unsigned int verticesSize,
        unsigned int indicesSize,
        Texture *texture,
        Shader *shader,
        glm::mat4 transform);
};

#endif // !OBJECT_HPP