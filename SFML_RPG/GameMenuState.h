#pragma once

#include "GameState.h"
#include "GamePlayState.h"

class GameMenuState : public GameState
{
public:
	GameMenuState(Game* game);
	~GameMenuState();

	virtual void handleInput();
	virtual void update(sf::Time deltaTime);
	virtual void render(sf::Time deltaTime);

	void loadGame();

private:

	sf::View _view;

};

