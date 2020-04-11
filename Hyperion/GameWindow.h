#pragma once
#include "GraphicsEngine.h"
#include "Configuration.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <string>

const std::string WINDOW_NAME = "Hyperion";

class GameWindow
{
public:
	GameWindow();
	
private:
	GLFWwindow* window_;

	GraphicsEngine* graphics_;
	
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	void initWindow();

	void mainLoop();

	void cleanup();
};
