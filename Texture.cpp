#include "Texture.hpp"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

unsigned int Texture::blankTexture = 0;

//Create the constructor
Texture::Texture(std::string path)
{
    //Set the texture path
    this->path = path;
    //flip the texture vertically
    stbi_set_flip_vertically_on_load(true);
    //Load the texture data
    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    //Generate the texture
    glGenTextures(1, &ID);
    //Bind the texture
    glBindTexture(GL_TEXTURE_2D, ID);
    //Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    //Set the texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //Check if the texture data loaded successfully
    if (data)
    {
        //Load the texture data into the texture
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);	
        //Generate the mipmap
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        //Print an error message
        std::cout << "Failed to load texture" << std::endl;
    }
    //Free the texture data
    stbi_image_free(data);
}

void Texture::initBlankTexture()
{
    //Generate the blank texture as a 1x1 white texture
    glGenTextures(1, &blankTexture);
    glBindTexture(GL_TEXTURE_2D, blankTexture);
    unsigned char data[] = {255, 255, 255};
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    //Set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T,  GL_REPEAT);
    //Set the texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,  GL_NEAREST);
}

//Create the destructor
Texture::~Texture()
{
    //Delete the texture
    glDeleteTextures(1, &ID);
}

//Bind the texture
void Texture::bind()
{
    //Bind the texture
    glBindTexture(GL_TEXTURE_2D, ID);
}

//Unbind the texture
void Texture::unbind()
{
    //Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);
}
