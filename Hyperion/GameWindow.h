#pragma once
#include "GraphicsEngine.h"
#include "Configuration.h"
#include "Camera.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#define LOGURU_WITH_STREAMS 1
#include "loguru.hpp"

#include <string>

const std::string WINDOW_NAME = "Hyperion";

class GameWindow
{
public:
	GameWindow();
	
private:
	GLFWwindow* window_;

	GraphicsEngine* graphics_;

	Camera* camera_;

	static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

	void initWindow();

	void mainLoop();

	void cleanup();
};
