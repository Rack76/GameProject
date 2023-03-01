#include "Input.h"
#include "../Game.h"
#include "WindowManager.h"
#include "Renderer.h"
#include "glfw3.h"

void cursorMoveCallback(GLFWwindow* window, double x, double y);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

Input::Input(Game* _game)
{
	game = _game;
}

void Input::init()
{
	glfwSetInputMode(game->windowManager->getWindow(0), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	if (glfwRawMouseMotionSupported())
		glfwSetInputMode(game->windowManager->getWindow(0), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
	glfwSetCursorPosCallback(game->windowManager->getWindow(0), cursorMoveCallback);
	glfwSetWindowUserPointer(game->windowManager->getWindow(0), game->renderer);
	glfwSetKeyCallback(game->windowManager->getWindow(0), keyCallback);
	glfwSetCursorPos(game->windowManager->getWindow(0), 400, 300);
}


void cursorMoveCallback(GLFWwindow* window, double x, double y)
{
	Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
	renderer->rotateCamera(window, x, y);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
		}
	}
	Renderer* renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(window));
	renderer->translateCamera(window, key, action);
}

void Input::update()
{
	glfwPollEvents();
}