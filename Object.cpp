#include "Object.hpp"
#include "shader.hpp"

void Object::render()
{
    static bool printed = false;
    // Bind the VAO
    glBindVertexArray(VAO);
    // std::cout << "Bound VAO" << std::endl;
    // Bind the texture
    if (texture != nullptr)
    {
        texture->bind();
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, Texture::blankTexture);
    }
    // std::cout << "Bound texture" << std::endl;
    // Use the shader program
    shader->use();
    // std::cout << "Used shader program" << std::endl;
    // Set the transform matrix
    shader->use();
    glUniformMatrix4fv(glGetUniformLocation(shader->ID, "model"), 1, GL_FALSE, glm::value_ptr(transform));
    // std::cout << "Set transform matrix" << std::endl;
    // Draw the object
    glDrawElements(GL_TRIANGLES, indicesSize, GL_UNSIGNED_INT, 0);
    // std::cout << "Drew object" << std::endl;
    // unbind the texture
    if (texture != nullptr)
    {
        texture->unbind();
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
    // std::cout << "Unbound texture" << std::endl;
    printed = true;
}

// Generate an implementation for the constructor defined in the header file that creates the opengl objects and loads the data into them
Object::Object(
    float *verticesArray,
    unsigned int *indicesArray,
    unsigned int verticesSize,
    unsigned int indicesSize,
    Texture *texture,
    Shader *shader,
    glm::mat4 transform)
{
    this->transform = transform;
    // Set the vertices array
    this->verticesArray = verticesArray;
    // Set the indices array
    this->indicesArray = indicesArray;
    // Set the vertices size
    this->verticesSize = verticesSize;
    // Set the indices size
    this->indicesSize = indicesSize;
    // Set the vertices size in bytes
    verticesSizeBytes = verticesSize * sizeof(float);
    // Set the indices size in bytes
    indicesSizeBytes = indicesSize * sizeof(unsigned int);
    unsigned int stride = 12 * sizeof(float);

    // Generate the VAO
    glGenVertexArrays(1, &VAO);
    // Generate the VBO
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    // Load the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, verticesSizeBytes, verticesArray, GL_STATIC_DRAW);
    // Load the indices into the EBO
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSizeBytes, indicesArray, GL_STATIC_DRAW);
    // Set the vertex attribute pointer for the vertex coordinates
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void *)0);

    // Enable the vertex attribute pointer for the vertex coordinates
    glEnableVertexAttribArray(0);
    // Set the vertex attribute pointer for the vertex color
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void *)(3 * sizeof(float)));
    // Enable the vertex attribute pointer for the vertex color
    glEnableVertexAttribArray(1);
    // Set the vertex attribute pointer for the vertex texture coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, stride, (void *)(7 * sizeof(float)));
    // Enable the vertex attribute pointer for the vertex texture coordinates
    glEnableVertexAttribArray(2);
    // Set the vertex attribute pointer for the vertex normal vector
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, stride, (void *)(9 * sizeof(float)));
    // Enable the vertex attribute pointer for the vertex normal vector
    glEnableVertexAttribArray(3);
    // Unbind the VAO
    glBindVertexArray(0);
    // Unbind the VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    // Unbind the EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // Generate the shader program
    this->shader = shader;
    this->texture = texture;
    // Bind the texture
    if (texture != nullptr)
    {
        texture->bind();
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, Texture::blankTexture);
    }
    // Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // Set the texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    if (texture != nullptr)
    {
        texture->unbind();
    }
    else
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}