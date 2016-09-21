#pragma once

#include "GameState.h"

class GamePlayState : public GameState
{
public:
	GamePlayState(Game* game);
	~GamePlayState();

	virtual void handleInput();
	virtual void update(sf::Time deltaTime);
	virtual void render(sf::Time deltaTime);

private:

	sf::View _view;
};

