#include <cassert>
#include "glfw3.h"
#include "WindowManager.h"

void WindowManager::init()
{
	if (!glfwInit())
	{
		assert(false && "couldnt initialize glfw!");
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	windows.push_back(glfwCreateWindow(800, 600, "window", nullptr, nullptr));
	windowCount++;

	for (auto window : windows)
	{
		if (!window)
		{
			assert(false && "couldnt initialize window!");
			glfwTerminate();
		}
		glfwMakeContextCurrent(window);
	}
}

void WindowManager::selectWindow(int index)
{
	glfwMakeContextCurrent(windows[index]);
	selectedWindow = index;
}

GLFWwindow* WindowManager::getSelectedWindow()
{
	return windows[selectedWindow];
}

GLFWwindow* WindowManager::getWindow(int index)
{
	if(index < windowCount)
		return windows[index];
	else
		assert(false && "window index is out of bounds!");
}
