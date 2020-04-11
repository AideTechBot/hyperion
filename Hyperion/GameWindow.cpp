#include "GameWindow.h"

GameWindow::GameWindow():
	window_(nullptr)
{
	initWindow();

	graphics_ = new GraphicsEngine(window_);

	mainLoop();
	cleanup();
}

void GameWindow::initWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    window_ = glfwCreateWindow(
        Configuration::getInstance().getWindowWidth(),
        Configuration::getInstance().getWindowHeight(),
        "Vulkan",
        nullptr,
        nullptr
    );
    glfwSetWindowUserPointer(window_, this);
    glfwSetFramebufferSizeCallback(window_, framebufferResizeCallback);
}

void GameWindow::mainLoop() {
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
        graphics_->drawFrame();
    }

    graphics_->deviceWaitIdle();
}

void GameWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<GameWindow*>(glfwGetWindowUserPointer(window));
    app->graphics_->frameBufferResized();
}

void GameWindow::cleanup()
{
    graphics_->cleanup();
	
    glfwDestroyWindow(window_);

    glfwTerminate();
}
