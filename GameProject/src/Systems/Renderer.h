#pragma once

#include <string>
class Game;
class GLFWwindow;

class Renderer {
public:
	Renderer(Game*);
	void init();
	void update();
	void rotateCamera(GLFWwindow*, double x, double y);
	void translateCamera(GLFWwindow* window, int key, int action);
private:
	void createShaderPrograms();
	void checkCompileErrors(unsigned int shader, std::string type);
	void loadGraphicsComponents();
	void loadGraphicsComponent(int i);
	Game* game;
};