#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"
#include <cassert>

#include "shader.h"
#include "VAO.h"

//Screen height and width
const unsigned int width = 800, height = 600;

//temp
GLdouble vertices[] = {
	-1.0, -1.0, 0.0,
	 1.0, -1.0, 0.0,
	 1.0,  1.0, 0.0
};

int  main(int argc, char** argv)
{
	GLFWwindow* window;
	
	
	if (!glfwInit())
	{
		assert(false && "couldnt initialize glfw!");
		return -1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, "window", nullptr, nullptr);

	if (!window)
	{
		assert(false && "couldnt initialize window!");
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
	}
	std::cerr << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

	//glViewport(0, 0, 800, 600);

	Shader shaderProgram("vertex.vs","fragment.fs");
	VAO VAO1;
	VAO1.Bind();
	VBO VBO1(vertices, sizeof(vertices));

	//Links VBO to VAO
	VAO1.LinkVBO(VBO1, 0);

	VAO1.Unbind();

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