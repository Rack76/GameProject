#include "glew.h"
#include "glfw3.h"
#include <cassert>

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

	while (!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
}