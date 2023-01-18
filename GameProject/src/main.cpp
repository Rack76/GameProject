#define GLEW_STATIC
#include "glew.h"
#include "glfw3.h"
#include <cassert>
#include "Game.h"

//Screen height and width
const unsigned int width = 800, height = 600;

int  main(int argc, char** argv)
{
	Game game;

	game.init();
	game.run();
}