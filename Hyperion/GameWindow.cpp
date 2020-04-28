#include "GameWindow.h"

GameWindow::GameWindow():
	window_(nullptr)
{
    LOG_S(INFO) << "Loading window";
	
	initWindow();

    camera_ = new Camera(glm::vec3(2.0f, 0.0f, 2.0f), glm::vec3(-2.0f, 0.0f, -2.0f));
	graphics_ = new GraphicsEngine(window_, camera_);

    LOG_S(INFO) << "Entering mainLoop";
	mainLoop();
    LOG_S(INFO) << "Exiting window and cleaning up";
	cleanup();
}

void GameWindow::initWindow()
{
    glfwInit();

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

    // TODO: rename window title to game name constant
    window_ = glfwCreateWindow(
        Configuration::getInstance().getWindowWidth(),
        Configuration::getInstance().getWindowHeight(),
        "Vulkan",
        nullptr,
        nullptr
    );
    glfwMaximizeWindow(window_);

    glfwSetWindowUserPointer(window_, this);
    glfwSetFramebufferSizeCallback(window_, framebufferResizeCallback);

    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetKeyCallback(window_, keyCallback);

    glfwSetCursorPosCallback(window_, cursorPositionCallback);
}

void GameWindow::mainLoop() {
    while (!glfwWindowShouldClose(window_)) {
        glfwPollEvents();
        graphics_->drawFrame();
    }

    glfwSetInputMode(window_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    graphics_->deviceWaitIdle();
}

void GameWindow::cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	static bool firstMousePass_ = true;
	static float lastX_, lastY_;

    if (firstMousePass_)
    {
        lastX_ = static_cast<float>(xpos);
        lastY_ = static_cast<float>(ypos);
        firstMousePass_ = false;
    }

    float xoffset = static_cast<float>(xpos) - lastX_;
    float yoffset = lastY_ - static_cast<float>(ypos);
    lastX_ = static_cast<float>(xpos);
    lastY_ = static_cast<float>(ypos);

	const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    // DLOG_S(INFO) << xoffset << " " << yoffset;
    auto app = reinterpret_cast<GameWindow*>(glfwGetWindowUserPointer(window));
    app->camera_->incrementDirection(xoffset, yoffset);
}

void GameWindow::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }

    const double increment = 0.1;
    auto app = reinterpret_cast<GameWindow*>(glfwGetWindowUserPointer(window));
	if (key == GLFW_KEY_W && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        app->camera_->moveForward(increment);
    } else if (key == GLFW_KEY_S && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        app->camera_->moveBack(increment);
    } else if (key == GLFW_KEY_A && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        app->camera_->strafeLeft(increment);
    } else if (key == GLFW_KEY_D && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        app->camera_->strafeRight(increment);
    }else if (key == GLFW_KEY_LEFT_SHIFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        app->camera_->moveUp(increment);
    }else if (key == GLFW_KEY_LEFT_CONTROL && (action == GLFW_PRESS || action == GLFW_REPEAT))
    {
        app->camera_->moveDown(increment);
    }
}

void GameWindow::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<GameWindow*>(glfwGetWindowUserPointer(window));
    app->graphics_->frameBufferResized();
    LOG_S(INFO) << "FrameBuffer resized";
}

void GameWindow::cleanup()
{
    graphics_->cleanup();
	
    glfwDestroyWindow(window_);

    glfwTerminate();
}
