#pragma once
#include "Entity.h"
class Enemy : public Entity
{
public:
	Enemy(sf::Texture* texture, sf::Vector2f position);
	~Enemy();

	void update(sf::Time _deltaTime);
	void render(sf::RenderWindow &_window);
	void processEvents(sf::Event &event);

private:

	sf::Sprite _body;

	bool _isMovingUp = false;
	bool _isMovingDown = false;
	bool _isMovingLeft = false;
	bool _isMovingRight = false;

	float _enemySpeed = 100;
};

