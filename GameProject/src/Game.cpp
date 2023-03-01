
#include "Game.h"
#include "Systems/Renderer.h"
#include "ComponentTypes.h"
#include "Systems/WindowManager.h"
#include "Systems/EntityManager.h"
#include "Systems/ComponentManager.h"
#include "Systems/Input.h"
#include "glfw3.h"

void Game::init()
{
	input = new Input(this);
	renderer = new Renderer(this);
	componentManager = new ComponentManager();
	windowManager = new WindowManager();
	entityManager = new EntityManager();
	componentManager->createComponent(GRAPHICS);
	Graphics* graphicsComponent0 = (Graphics*)componentManager->getComponent(GRAPHICS, 0);
	graphicsComponent0->vertexPath = "vertex.vs";
	graphicsComponent0->fragmentPath = "fragment.fs";
	input->init();
	renderer->init();
}

void Game::run()
{
	while (!glfwWindowShouldClose(windowManager->getWindow(0)))
	{
		renderer->update();
		input->update();
	}
}

void Game::cleanUp()
{
	componentManager->cleanUp();
}