#pragma once
#include "Game.h"
class Game;
class GameState
{
public:
	GameState();
	~GameState();

	Game* _game;

	virtual void handleInput() = 0;
	virtual void update(sf::Time deltaTime) = 0;
	virtual void render(sf::Time deltaTime) = 0;
};

