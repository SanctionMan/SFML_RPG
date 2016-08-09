#include "Player.h"



Player::Player(sf::Texture* texture, sf::Vector2f position):
	_body()
{
	_position.x = position.x;
	_position.y = position.y;

	_body.setTexture(*texture);
	_body.setPosition(sf::Vector2f(_position.x, _position.y));
	_body.setOrigin(sf::Vector2f(_body.getGlobalBounds().height / 2, _body.getGlobalBounds().width / 2));
	//_body.setScale(sf::Vector2f(.5, .5));
	
	_bounds.setSize(sf::Vector2f(_body.getGlobalBounds().height, _body.getGlobalBounds().width));
	_bounds.setPosition(sf::Vector2f(_position.x, _position.y));
	_bounds.setOrigin(sf::Vector2f(_body.getGlobalBounds().height / 2, _body.getGlobalBounds().width / 2));
	_bounds.setOutlineThickness(1);
	_bounds.setOutlineColor(sf::Color::Green);
	_bounds.setFillColor(sf::Color(0, 0, 0, 0));

	_name = "Player";
}

Player::~Player()
{
}

void Player::update(sf::Time _deltaTime)
{
	// Update Movement
	sf::Vector2f movement(0.f, 0.f);
	if (_isMovingUp)
		movement.y -= _playerSpeed;
	if (_isMovingDown)
		movement.y += _playerSpeed;
	if (_isMovingLeft)
		movement.x -= _playerSpeed;
	if (_isMovingRight)
		movement.x += _playerSpeed;
	_bounds.move(movement * _deltaTime.asSeconds());

	// Update _positions and _body
	_position = _bounds.getPosition();
	_body.setPosition(_position.x, _position.y);

}

void Player::render(sf::RenderWindow &_window)
{
	_window.draw(_bounds);
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
