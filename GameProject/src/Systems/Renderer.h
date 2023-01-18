#pragma once

#include <string>
class Game;

class Renderer {
public:
	Renderer(Game*);
	void init();
	void update();
	void deleteGraphicsComponent(int);
private:
	void createShaderPrograms();
	void checkCompileErrors(unsigned int shader, std::string type);
	void genBuffers();
	Game* game;
};