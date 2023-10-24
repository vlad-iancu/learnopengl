#ifndef OPENGL_RENDER_H
#define OPENGL_RENDER_H
#include <GLFW/glfw3.h>
#include <thread>

void init(GLFWwindow *window);
void render(GLFWwindow *window);
void camera_handler(GLFWwindow *window);
void window_handler(int width, int height);
//extern std::thread moveLightThread;
#endif
