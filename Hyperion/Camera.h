#pragma once
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#define LOGURU_WITH_STREAMS 1
#include "loguru.hpp"

#include <chrono>

class Camera
{
	const float FOV = glm::radians(60.0f);
	const float Z_NEAR = 0.001f;
	const float Z_FAR = 10.0f;
public:
	glm::vec3 position;
	glm::vec3 viewDirection;
	glm::vec3 up;
	glm::vec3 right;
	float yaw = 0.0f;
	float pitch = 0.0f;

	Camera(glm::vec3 pos, glm::vec3 dir);

	glm::mat4 getModelToWorldMatrix() const;
	glm::mat4 getWorldToViewMatrix() const;
	glm::mat4 getViewToProjectionMatrix(float aspectRatio) const;

	void incrementDirection(float yaw, float pitch);

	void moveForward(float delta);
	void moveBack(float delta);
	void strafeLeft(float delta);
	void strafeRight(float delta);
	void moveUp(float delta);
	void moveDown(float delta);
};
