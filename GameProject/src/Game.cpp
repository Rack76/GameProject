#include "Game.h"
#include "ComponentTypes.h"

void Game::init()
{
	componentManager.createComponent(GRAPHICS);
	Graphics* graphicsComponent0 = componentManager.getComponent(GRAPHICS, 0);
	graphicsComponent0->vertexPath = "vertex.vs";
	graphicsComponent0->fragmentPath = "fragment.fs";
	renderer.init();
}

void Game::run()
{
	while (1)
	{
		renderer.update();
	}
}
