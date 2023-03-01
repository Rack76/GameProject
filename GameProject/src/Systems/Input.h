#pragma once

class Game;

class Input {
public:
	Input(Game*);
	void init();
	void update();

private:
	Game* game;
};