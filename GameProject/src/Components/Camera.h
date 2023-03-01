#pragma once

#include "glm/ext/vector_float3.hpp"
#include "glm/ext/matrix_float3x3.hpp"
#include "glm/gtc/matrix_transform.hpp"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Component.h"

class Camera : public Component
{
public:
	Camera() : Component() {
		position = glm::vec3(0.0, 0.0, 0.0);
		velocity = glm::vec3(0.0, 0.0, 0.0);
		orientation = glm::mat3(1.0);
		perspective = glm::perspective(0.6, 1.2, 0.1, 300.0);
	}
	glm::vec3 position;
	glm::vec3 velocity;
	glm::mat3 orientation;
	glm::mat4 perspective;
};