#include "Player.h"



Player::Player(sf::Texture* texture, sf::Vector2f position):
	_textureBody(texture)
{
	_position = position;
	
	// Setup collision bounds
	_bounds.setSize(sf::Vector2f(60,60));
	_bounds.setPosition(sf::Vector2f(_position.x, _position.y));
	//_bounds.setOrigin(sf::Vector2f(_body.getGlobalBounds().height / 2, _body.getGlobalBounds().width / 2));
	_bounds.setOutlineThickness(1);
	_bounds.setOutlineColor(sf::Color::Green);
	_bounds.setFillColor(sf::Color(0, 0, 0, 0));

	// Set entitie name
	_name = "Player";

	// Set player textures for animations
	initPlayerTextures();
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
	_animatedBody.setPosition(_position.x, _position.y);

	// Update Animation
	_animatedBody.play(*_currentAnimation);
	_animatedBody.update(_deltaTime);

	// Animation State
	if (!_isMovingUp && !_isMovingDown && !_isMovingLeft && !_isMovingRight)
	{
		_isIdle = true;
		_currentAnimation = &_stanceAnimationDown;
	}

}

void Player::render(sf::RenderWindow &_window)
{
	_window.draw(_bounds);
	_window.draw(_animatedBody);
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
	{
		_isMovingUp = isPressed;
		_currentAnimation = &_runningAnimationUp;
	}
	else if (key == sf::Keyboard::S) 
	{
		_isMovingDown = isPressed;
		_currentAnimation = &_runningAnimationDown;
	}
	else if (key == sf::Keyboard::A)
	{
		_isMovingLeft = isPressed;
		_currentAnimation = &_runningAnimationLeft;
	}
	else if (key == sf::Keyboard::D)
	{
		_isMovingRight = isPressed;
		_currentAnimation = &_runningAnimationRight;
	}
}

void Player::initPlayerTextures()
{
	// Set textures for animations

	// Stance (4 frames)
	{
		_stanceAnimationUp.setSpriteSheet(*_textureBody);
		_stanceAnimationUp.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationUp.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationUp.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationUp.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationDown.setSpriteSheet(*_textureBody);
		_stanceAnimationDown.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationDown.addFrame(sf::IntRect(128, 790, 128, 128));
		_stanceAnimationDown.addFrame(sf::IntRect(128 * 2, 790, 128, 128));
		//_stanceAnimationDown.addFrame(sf::IntRect(128 * 3, 790, 32, 32)); THIS IS NOT WORKING (OUT OF RANGE)
		_stanceAnimationLeft.setSpriteSheet(*_textureBody);
		_stanceAnimationLeft.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationLeft.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationLeft.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationLeft.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationRight.setSpriteSheet(*_textureBody);
		_stanceAnimationRight.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationRight.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationRight.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationRight.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationUp_Left.setSpriteSheet(*_textureBody);
		_stanceAnimationUp_Left.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationUp_Left.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationUp_Left.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationUp_Left.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationUp_Right.setSpriteSheet(*_textureBody);
		_stanceAnimationUp_Right.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationUp_Right.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationUp_Right.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationUp_Right.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationDown_Left.setSpriteSheet(*_textureBody);
		_stanceAnimationDown_Left.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationDown_Left.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationDown_Left.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationDown_Left.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationDown_Right.setSpriteSheet(*_textureBody);
		_stanceAnimationDown_Right.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationDown_Right.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationDown_Right.addFrame(sf::IntRect(0, 790, 128, 128));
		_stanceAnimationDown_Right.addFrame(sf::IntRect(0, 790, 128, 128));
	}

	// Running (8 frames)
	{
		_runningAnimationUp.setSpriteSheet(*_textureBody);
		_runningAnimationUp.addFrame(sf::IntRect(128 * 4,  128 * 2, 128, 128)); //Done
		_runningAnimationUp.addFrame(sf::IntRect(128 * 5,  128 * 2, 128, 128));
		_runningAnimationUp.addFrame(sf::IntRect(128 * 6,  128 * 2, 128, 128));
		_runningAnimationUp.addFrame(sf::IntRect(128 * 7,  128 * 2, 128, 128));
		_runningAnimationUp.addFrame(sf::IntRect(128 * 8,  128 * 2, 128, 128));
		_runningAnimationUp.addFrame(sf::IntRect(128 * 9,  128 * 2, 128, 128));
		_runningAnimationUp.addFrame(sf::IntRect(128 * 10, 128 * 2, 128, 128));
		_runningAnimationUp.addFrame(sf::IntRect(128 * 11, 128 * 2, 128, 128));
		_runningAnimationDown.setSpriteSheet(*_textureBody);
		_runningAnimationDown.addFrame(sf::IntRect(128 * 4,  128 * 6, 128, 128)); //Done
		_runningAnimationDown.addFrame(sf::IntRect(128 * 5,  128 * 6, 128, 128));
		_runningAnimationDown.addFrame(sf::IntRect(128 * 6,  128 * 6, 128, 128));
		_runningAnimationDown.addFrame(sf::IntRect(128 * 7,  128 * 6, 128, 128));
		_runningAnimationDown.addFrame(sf::IntRect(128 * 8,  128 * 6, 128, 128));
		_runningAnimationDown.addFrame(sf::IntRect(128 * 9,  128 * 6, 128, 128));
		_runningAnimationDown.addFrame(sf::IntRect(128 * 10, 128 * 6, 128, 128));
		_runningAnimationDown.addFrame(sf::IntRect(128 * 11, 128 * 6, 128, 128));
		_runningAnimationLeft.setSpriteSheet(*_textureBody);
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 4,  128 * 0, 128, 128)); //Done
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 5,  128 * 0, 128, 128));
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 6,  128 * 0, 128, 128));
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 7,  128 * 0, 128, 128));
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 8,  128 * 0, 128, 128));
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 9,  128 * 0, 128, 128));
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 10, 128 * 0, 128, 128));
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 11, 128 * 0, 128, 128));
		_runningAnimationRight.setSpriteSheet(*_textureBody);
		_runningAnimationRight.addFrame(sf::IntRect(128 * 4,  128 * 4, 128, 128)); //Done
		_runningAnimationRight.addFrame(sf::IntRect(128 * 5,  128 * 4, 128, 128));
		_runningAnimationRight.addFrame(sf::IntRect(128 * 6,  128 * 4, 128, 128));
		_runningAnimationRight.addFrame(sf::IntRect(128 * 7,  128 * 4, 128, 128));
		_runningAnimationRight.addFrame(sf::IntRect(128 * 8,  128 * 4, 128, 128));
		_runningAnimationRight.addFrame(sf::IntRect(128 * 9,  128 * 4, 128, 128));
		_runningAnimationRight.addFrame(sf::IntRect(128 * 10, 128 * 4, 128, 128));
		_runningAnimationRight.addFrame(sf::IntRect(128 * 11, 128 * 4, 128, 128));
		_runningAnimationUp_Left.setSpriteSheet(*_textureBody);
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 4,  128 * 1, 128, 128)); //DONE
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 5,  128 * 1, 128, 128));
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 6,  128 * 1, 128, 128));
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 7,  128 * 1, 128, 128));
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 8,  128 * 1, 128, 128));
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 9,  128 * 1, 128, 128));
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 10, 128 * 1, 128, 128));
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 11, 128 * 1, 128, 128));
		_runningAnimationUp_Right.setSpriteSheet(*_textureBody);
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 4,  128 * 3, 128, 128)); //Done
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 5,  128 * 3, 128, 128));
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 6,  128 * 3, 128, 128));
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 7,  128 * 3, 128, 128));
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 8,  128 * 3, 128, 128));
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 9,  128 * 3, 128, 128));
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 10, 128 * 3, 128, 128));
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 11, 128 * 3, 128, 128));
		_runningAnimationDown_Left.setSpriteSheet(*_textureBody);
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 4,  128 * 7, 128, 128)); //Done
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 5,  128 * 7, 128, 128));
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 6,  128 * 7, 128, 128));
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 7,  128 * 7, 128, 128));
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 8,  128 * 7, 128, 128));
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 9,  128 * 7, 128, 128));
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 10, 128 * 7, 128, 128));
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 11, 128 * 7, 128, 128));
		_runningAnimationDown_Right.setSpriteSheet(*_textureBody);
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 4,  128 * 5, 128, 128)); //Done
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 5,  128 * 5, 128, 128));
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 6,  128 * 5, 128, 128));
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 7,  128 * 5, 128, 128));
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 8,  128 * 5, 128, 128));
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 9,  128 * 5, 128, 128));
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 10, 128 * 5, 128, 128));
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 11, 128 * 5, 128, 128));
	}
	// Melee Swing (4 frames)

	// Block (2 frames)

	// Hit and Die (6 frames)

	// Cast Spell (4 frames)

	// Shoot Bow (4 frames)

	// Create pointer to current animation
	Animation* _currentAnimation = &_stanceAnimationDown;

	// Setup animatedsprite
	AnimatedSprite _animatedBody(sf::seconds(0.1), true, false);
	_animatedBody.setPosition(sf::Vector2f(50, 50));
}
