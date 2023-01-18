#pragma once

#include "glew.h"

struct Graphics
{
	GLuint vboID;
	GLuint vaoID;
	GLuint shaderID;
	const char* vertexPath;
	const char* fragmentPath;
};