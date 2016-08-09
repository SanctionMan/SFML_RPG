#pragma once
#include "Entity.h"
#include "Game.h"
class Player : public Entity
{
public:
	Player(sf::Texture* texture, sf::Vector2f position);
	~Player();

	void update(sf::Time _deltaTime);
	void render(sf::RenderWindow &_window);
	void processEvents(sf::Event &event);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:

	sf::Sprite _body;

	bool _isMovingUp = false;
	bool _isMovingDown = false;
	bool _isMovingLeft = false;
	bool _isMovingRight = false;

	float _playerSpeed = 100;
};

