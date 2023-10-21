#include "Camera.hpp"

void Camera::processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        zoomIn(1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        zoomOut(1.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        rotateHorizontally(2.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        rotateHorizontally(-2.0);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        rotateVertically(2.0f);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        rotateVertically(-2.0f);
    }
}
void Camera::zoomOut(float distance)
{
    if (fov + distance < 180.0f)
        this->fov += distance;
    computeTransformations();
}

void Camera::zoomIn(float distance)
{
    if (fov - distance > 0.0f)
        this->fov -= distance;
    computeTransformations();
}

void Camera::rotateVertically(float angle)
{
    if (pitchAngle + angle > 89.0f || pitchAngle + angle < -89.0f)
    {
        return;
    }
    pitchAngle += angle;
    computeTransformations();
}

void Camera::rotateHorizontally(float angle)
{
    yawAngle += angle;
    computeTransformations();
}

Camera::Camera(
    glm::vec3 cameraTarget,
    float yawAngle,
    float pitchAngle,
    float distance,
    int width,
    int height,
    Shader *shaders,
    int numShaders)
{
    // Camera up vector is the cross product of the camera position and camera target
    this->shaders = shaders;
    this->cameraTarget = cameraTarget;
    this->distance = distance;
    this->yawAngle = yawAngle;
    this->pitchAngle = pitchAngle;
    this->width = width;
    this->height = height;
    this->numShaders = numShaders;
    computeTransformations();
}
void Camera::computeTransformations()
{
    // Compute the view matrix direction vector based on yaw and pitch angles
    glm::vec3 direction;
    direction.x = distance * cos(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));
    direction.y = distance * sin(glm::radians(pitchAngle));
    direction.z = distance * sin(glm::radians(yawAngle)) * cos(glm::radians(pitchAngle));
    glm::vec3 up = glm::vec3(0.0, 1.0, 0.0);
    glm::vec3 cameraRight = glm::normalize(glm::cross(up, direction));
    glm::vec3 cameraUp = glm::cross(direction, cameraRight);
    std::cout << yawAngle << " " << pitchAngle << std::endl;
    view = glm::lookAt(cameraTarget + direction, cameraTarget, cameraUp);
    if (width == 0 || height == 0)
    {
        std::cout << "Width or height is 0" << std::endl;
        return;
    }
    projection = glm::perspective(glm::radians(fov), (float)width / (float)height, 0.1f, 100.0f);

    for (int i = 0; i < numShaders; i++)
    {
        shaders[i].use();
        glUniformMatrix4fv(glGetUniformLocation(shaders[i].ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(glGetUniformLocation(shaders[i].ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
    
    }
}

int Camera::getWidth()
{
    return width;
}

void Camera::setWidth(int width)
{
    this->width = width;
}

int Camera::getHeight()
{
    return height;
}

void Camera::setHeight(int height)
{
    this->height = height;
}