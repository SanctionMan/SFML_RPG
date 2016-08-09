#include "Player.h"



Player::Player(sf::Texture* texture, sf::Vector2f position):
	_body()
{
	_position.x = position.x;
	_position.y = position.y;

	_body.setTexture(*texture);
	_body.setPosition(sf::Vector2f(_position.x, _position.y));

	_name = "Player";
}


Player::~Player()
{
}

void Player::update(sf::Time _deltaTime)
{
	//Update _position
	//_position = _body.getPosition();

	sf::Vector2f movement(0.f, 0.f);
	if (_isMovingUp)
		movement.y -= _playerSpeed;
	if (_isMovingDown)
		movement.y += _playerSpeed;
	if (_isMovingLeft)
		movement.x -= _playerSpeed;
	if (_isMovingRight)
		movement.x += _playerSpeed;
	_body.move(movement * _deltaTime.asSeconds());

}

void Player::render(sf::RenderWindow &_window)
{
	_window.draw(_body);
}

void Player::processEvents(sf::Event & event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		handlePlayerInput(event.key.code, true);
		break;
	case sf::Event::KeyReleased:
		handlePlayerInput(event.key.code, false);
		break;
	}
}

void Player::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		_isMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		_isMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		_isMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		_isMovingRight = isPressed;
}
