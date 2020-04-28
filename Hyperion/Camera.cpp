#include "Camera.h"

Camera::Camera(glm::vec3 pos, glm::vec3 dir):
	position(pos),
	viewDirection(dir),
	up(glm::vec3(0.0f, 0.0f, 1.0f)),
	right(-glm::cross(up, viewDirection))
{	}

glm::mat4 Camera::getModelToWorldMatrix() const
{
    static auto startTime = std::chrono::high_resolution_clock::now();
    
    auto currentTime = std::chrono::high_resolution_clock::now();
    float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
	// return glm::rotate(glm::mat4(1.0f), time * glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	return glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
}

glm::mat4 Camera::getWorldToViewMatrix() const
{
	return glm::lookAt(position, position + viewDirection, up);
}

glm::mat4 Camera::getViewToProjectionMatrix(float aspectRatio) const
{
	return glm::perspective(FOV, aspectRatio, Z_NEAR, Z_FAR);
}

void Camera::incrementDirection(float xoffset, float yoffset)
{
    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // DLOG_S(INFO) << yaw << " " << pitch;

    glm::vec3 front;
    front.x = -cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.z = sin(glm::radians(pitch));
    // DLOG_S(INFO) << front.x << " " << front.y << " " << front.z;

    right = -glm::cross(up, viewDirection);
    viewDirection = glm::normalize(front);
}

void Camera::moveForward(float delta)
{
    position += (delta * viewDirection);
}

void Camera::moveBack(float delta)
{
    position -= (delta * viewDirection);
}

void Camera::strafeLeft(float delta)
{
    position -= (delta * right);
}

void Camera::strafeRight(float delta)
{
    position += (delta * right);
}

void Camera::moveUp(float delta)
{
    position += (delta * up);
}

void Camera::moveDown(float delta)
{
    position -= (delta * up);
}
