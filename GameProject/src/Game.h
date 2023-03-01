#pragma once

class WindowManager;
class Renderer;
class EntityManager;
class ComponentManager;
class Input;

class Game {
public:

	Game() {
		
	}
	void init();
	void run();
	void cleanUp();
	WindowManager* windowManager;
	Renderer* renderer;
	Input* input;
	EntityManager* entityManager;
	ComponentManager* componentManager;
};