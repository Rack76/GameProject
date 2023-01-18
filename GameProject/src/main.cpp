#include "glew.h"
#include "glfw3.h"
#include <cassert>

#include "shader.h"
#include "VAO.h"

//temp
GLfloat vertices[] = {
	-1.0f, -1.0f, 0.0f,
	 1.0f, -1.0f, 0.0f,
	 1.0f,  1.0f, 0.0f
};

int  main(int argc, char** argv)
{
	GLFWwindow* window;

	if (!glewInit())
	{
		assert(false && "couldnt initialize glew!");
		return -1;
	}

	if (!glfwInit())
	{
		assert(false && "couldnt initialize glfw!");
		return -1;
	}

	window = glfwCreateWindow(800, 600, "window", nullptr, nullptr);

	if (!window)
	{
		assert(false && "couldnt initialize window!");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	Shader shaderProgram("vertex.vs","fragment.fs");
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));

	//Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);

	VAO1.Unbind();
	VBO1.Unbind();

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		shaderProgram.use();
		VAO1.Bind();
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}