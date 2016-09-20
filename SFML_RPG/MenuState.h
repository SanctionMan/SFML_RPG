#pragma once

#include <SFML\Graphics.hpp>
#include "GameState.h"

class MenuState : public GameState
{
public:
	MenuState(Game* game);
	~MenuState();

	virtual void handleInput();
	virtual void update(sf::Time deltaTime);
	virtual void render(sf::Time deltaTime);

private:

	sf::View _view;
};

