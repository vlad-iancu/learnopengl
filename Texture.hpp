//Create header guard
#ifndef TEXTURE_HPP
#define TEXTURE_HPP
//Include dependencies
#include <string>
#include <glad/glad.h>
#include <GL/gl.h>

//Create a class for the texture
class Texture
{
    public:
        static unsigned int blankTexture;
        static void initBlankTexture();
    //Private members
    public:
        //The texture ID
        unsigned int ID;
        //The texture width
        int width;
        //The texture height
        int height;
        //The texture number of channels
        int nrChannels;
        //The texture data
        unsigned char *data;
        //The texture path
        std::string path;
        //The constructor
        Texture(std::string path);
        //The destructor
        ~Texture();
        //Bind the texture
        void bind();
        //Unbind the texture
        void unbind();
        //Get the texture ID
        unsigned int getID();
        //Get the texture width
        int getWidth();
        //Get the texture height
        int getHeight();
        //Get the texture number of channels
        int getNrChannels();
        //Get the texture data
        unsigned char* getData();
        //Get the texture path
        std::string getPath();
};
//End header guard
#endif