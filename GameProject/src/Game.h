#pragma once

#include "Systems/WindowManager.h"
#include "Systems/Renderer.h"
#include "Systems/EntityManager.h"
#include "Systems/ComponentManager.h"

class Game {
public:

	Game() {
		windowManager.init();
	}
	void init();
	void run();
	WindowManager windowManager;
	Renderer renderer;
	EntityManager entityManager;
	ComponentManager componentManager;
};