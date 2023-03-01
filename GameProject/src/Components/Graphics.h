#pragma once

#include "Component.h"
#include "glew.h"

struct Graphics : public Component
{
public:
	Graphics() : Component() {

	}
	GLuint vboID;
	GLuint vaoID;
	GLuint shaderID;
	const char* vertexPath;
	const char* fragmentPath;
};