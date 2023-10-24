#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "include/glad/glad.h"
#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include <GLFW/glfw3.h>
#include "shader.hpp"

//Create a camera class that represents an opengl camera, it has three attributes: camera position, camera target and camera up vector it has a function that returns the view matrix
// and a function that rotates the camera left and right
class Camera
{

    float yawAngle = 0.0;
    float pitchAngle = 0.0;
    float distance = 1.0;
    float fov = 45.0;
    Shader *shaders;
    int numShaders = 1;
    glm::vec3 cameraTarget;
    glm::mat4 view;
    glm::mat4 projection;
    glm::vec3 cameraPosition;
    int width = 800;
    int height = 600;

public:

    void computeTransformations();

    //Create a constructor that takes the camera position, camera target as parameters and computes camera up vector
    Camera(
        glm::vec3 cameraTarget, 
        float yawAngle, 
        float pitchAngle, 
        float distance, 
        int width, 
        int height, 
        Shader *shaders,
        int numShaders);
    void rotateHorizontally(float angle);
    //Create a function that rotates the camera vertically
    void rotateVertically(float angle);
    //Create a function that moves the camera forward
    void zoomIn(float distance);
    //Create a function that moves the camera backward
    void zoomOut(float distance);
    //Create a function that processes the input from the keyboard
    void processInput(GLFWwindow *window);
    //Getters and setters for width and height
    int getWidth();
    void setWidth(int width);
    int getHeight();
    void setHeight(int height);
};

#endif // CAMERA_HPP
