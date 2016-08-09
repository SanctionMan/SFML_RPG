#include "Enemy.h"



Enemy::Enemy(sf::Texture* texture, sf::Vector2f position):
	_body()
{
	_position.x = position.x;
	_position.y = position.y;

	_body.setTexture(*texture);
	_body.setPosition(sf::Vector2f(_position.x, _position.y));
	_body.setOrigin(sf::Vector2f(_body.getGlobalBounds().height / 2, _body.getGlobalBounds().width / 2));
	_body.setScale(sf::Vector2f(.5, .5));

	_bounds.setSize(sf::Vector2f(_body.getGlobalBounds().height, _body.getGlobalBounds().width));
	_bounds.setPosition(sf::Vector2f(_position.x, _position.y));
	_bounds.setOrigin(sf::Vector2f(_body.getGlobalBounds().height / 2, _body.getGlobalBounds().width / 2));
	_bounds.setOutlineThickness(1);
	_bounds.setOutlineColor(sf::Color::Green);
	_bounds.setFillColor(sf::Color(0, 0, 0, 0));

	_name = "Enemy";
}


Enemy::~Enemy()
{
}

void Enemy::update(sf::Time _deltaTime)
{
	// Update Movement
	sf::Vector2f movement(0.f, 0.f);
	if (_isMovingUp)
		movement.y -= _enemySpeed;
	if (_isMovingDown)
		movement.y += _enemySpeed;
	if (_isMovingLeft)
		movement.x -= _enemySpeed;
	if (_isMovingRight)
		movement.x += _enemySpeed;
	_bounds.move(movement * _deltaTime.asSeconds());

	// Update _positions and _body
	_position = _bounds.getPosition();
	_body.setPosition(_position.x, _position.y);
}

void Enemy::render(sf::RenderWindow & _window)
{
	_window.draw(_bounds);
	_window.draw(_body);
}

void Enemy::processEvents(sf::Event & event)
{
	// Nothing at this point in time
}
