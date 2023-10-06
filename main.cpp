#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <GL/gl.h>
#include "render.hpp"
#include <iostream>
#include "shader.hpp"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void process_input(GLFWwindow *window)
{
	if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

int main()
{
	int width = 1500;
	int height = 900;
	
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	
	GLFWwindow* window = glfwCreateWindow(
			width,
			//glfwGetVideoMode(glfwGetPrimaryMonitor())->width,
			height,
			//glfwGetVideoMode(glfwGetPrimaryMonitor())->height, 
			"Learn OpenGL",
			nullptr, 
			nullptr);
	if (window == nullptr)
	{
	std::cout << "Failed to create GLFW window" << std::endl;
	glfwTerminate();
	return -1;
	}
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	init();
	while(!glfwWindowShouldClose(window))
	{
		process_input(window);
		render(window);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
