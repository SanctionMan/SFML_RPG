#include "Player.h"



Player::Player(sf::Vector2f position, sf::Texture* headTexture, sf::Texture* bodyTexture) :
	_textureHead(headTexture),
	_textureBody(bodyTexture),
	_animatedHead(sf::seconds(0.2f), true, false),
	_animatedBody(sf::seconds(0.2f), true, false),
	_animationSize(128, 128)
{
	_position = position;
	_radius = 10;
	_mass = 5;
	_adjustment_xy = sf::Vector2f(0.f, 25.f);

	 // Setup collision bounds
	_bounds.setSize(sf::Vector2f(_animationSize.x / 4, _animationSize.y / 4));
	_bounds.setPosition(_position + _adjustment_xy);
	_bounds.setOrigin(_bounds.getSize() / 2.f);
	_bounds.setOutlineThickness(1);
	_bounds.setOutlineColor(sf::Color::Green);
	_bounds.setFillColor(sf::Color(0, 0, 0, 0));

	_shape.setRadius(_radius);
	_shape.setPosition(_position + _adjustment_xy);
	_shape.setOrigin(sf::Vector2f(_radius, _radius));
	_shape.setOutlineThickness(2);
	_shape.setOutlineColor(sf::Color::Red);
	_shape.setFillColor(sf::Color(0, 0, 0, 0));
	//_shape.scale(1.f, 0.55f);

	// Set entitie name
	_name = "Player";

	// Set player textures for animations
	initPlayerTextures();
	_animatedBody.setOrigin(sf::Vector2f(_animationSize.x / 2, _animationSize.y / 2));
	//_animatedBody.setScale(2, 2);
	_animatedHead.setOrigin(sf::Vector2f(_animationSize.x / 2, _animationSize.y / 2));
	//_animatedHead.setScale(2, 2);
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
	//_bounds.move(movement * _deltaTime.asSeconds());
	_shape.move(movement * _deltaTime.asSeconds());

	// Update _positions and _body
	_position = _shape.getPosition() - _adjustment_xy;
	_animatedBody.setPosition(_position);
	_animatedHead.setPosition(_position);
	_bounds.setPosition(_position + _adjustment_xy);

	// Update Animation
	_animatedBody.play(*_currentAnimationBody);
	_animatedBody.update(_deltaTime);
	_animatedHead.play(*_currentAnimationHead);
	_animatedHead.update(_deltaTime);

	// Set Animation State
	if (!_isMovingUp && !_isMovingDown && !_isMovingLeft && !_isMovingRight)
	{
		switch (_lastAnimationState)
		{
		case _movingUp:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationUp;
			_currentAnimationHead = &_Head_stanceAnimationDown;
			break;
		case _movingDown:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationDown;
			_currentAnimationHead = &_Head_stanceAnimationDown;
			break;
		case _movingLeft:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationLeft;
			_currentAnimationHead = &_Head_stanceAnimationLeft;
			break;
		case _movingRight:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationRight;
			_currentAnimationHead = &_Head_stanceAnimationRight;
			break;
		case _movingUp_Left:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationUp_Left;
			_currentAnimationHead = &_Head_stanceAnimationUp_Left;
			break;
		case _movingUp_Right:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationUp_Right;
			_currentAnimationHead = &_Head_stanceAnimationUp_Right;
			break;
		case _movingDown_Left:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationDown_Left;
			_currentAnimationHead = &_Head_stanceAnimationDown_Left;
			break;
		case _movingDown_Right:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationDown_Right;
			_currentAnimationHead = &_Head_stanceAnimationDown_Right;
			break;
		}
	
	}
	if (_isMovingUp)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationUp;
		_currentAnimationHead = &_Head_runningAnimationUp;
		_lastAnimationState = _movingUp;
	}
	if (_isMovingDown)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationDown;
		_currentAnimationHead = &_Head_runningAnimationDown;
		_lastAnimationState = _movingDown;
	}
	if (_isMovingLeft)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationLeft;
		_currentAnimationHead = &_Head_runningAnimationLeft;
		_lastAnimationState = _movingLeft;
	}
	if (_isMovingRight)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationRight;
		_currentAnimationHead = &_Head_runningAnimationRight;
		_lastAnimationState = _movingRight;
	}
	if (_isMovingUp && _isMovingLeft)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationUp_Left;
		_currentAnimationHead = &_Head_runningAnimationUp_Left;
		_lastAnimationState = _movingUp_Left;
	}
	if (_isMovingUp && _isMovingRight)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationUp_Right;
		_currentAnimationHead = &_Head_runningAnimationUp_Right;
		_lastAnimationState = _movingUp_Right;
	}
	if (_isMovingDown && _isMovingLeft)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationDown_Left;
		_currentAnimationHead = &_Head_runningAnimationDown_Left;
		_lastAnimationState = _movingDown_Left;
	}
	if (_isMovingDown && _isMovingRight)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationDown_Right;
		_currentAnimationHead = &_Head_runningAnimationDown_Right;
		_lastAnimationState = _movingDown_Right;
	}

}

void Player::render(sf::RenderWindow &_window)
{
	_window.draw(_bounds);
	_window.draw(_shape);
	_window.draw(_animatedBody);
	_window.draw(_animatedHead);
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
	}
	else if (key == sf::Keyboard::S) 
	{
		_isMovingDown = isPressed;
	}
	else if (key == sf::Keyboard::A)
	{
		_isMovingLeft = isPressed;
	}
	else if (key == sf::Keyboard::D)
	{
		_isMovingRight = isPressed;
	}
}

void Player::initPlayerTextures()
{
	// Set textures for animations

	initHeadTextures();
	initBodyTextures();
	initWeaponTextures();

	// Create pointer to current animation
	_currentAnimationHead = &_Head_stanceAnimationDown;
	_currentAnimationBody = &_stanceAnimationDown;

	// Setup animatedsprite
	//AnimatedSprite _animatedHead(sf::seconds(0.05), true, false);
	//AnimatedSprite _animatedBody(sf::seconds(0.05), true, false);
	_animatedHead.setPosition(_position);
	_animatedBody.setPosition(_position);
}

void Player::initBodyTextures()
{
	// Stance (4 frames)
	{
		_stanceAnimationUp.setSpriteSheet(*_textureBody);
		_stanceAnimationUp.addFrame(sf::IntRect(128 * 0, 128 * 2, 128, 128));
		_stanceAnimationUp.addFrame(sf::IntRect(128 * 1, 128 * 2, 128, 128));
		_stanceAnimationUp.addFrame(sf::IntRect(128 * 2, 128 * 2, 128, 128));
		_stanceAnimationUp.addFrame(sf::IntRect(128 * 3, 128 * 2, 128, 128));
		_stanceAnimationDown.setSpriteSheet(*_textureBody);
		_stanceAnimationDown.addFrame(sf::IntRect(128 * 0, 128 * 6, 128, 128));
		_stanceAnimationDown.addFrame(sf::IntRect(128 * 1, 128 * 6, 128, 128));
		_stanceAnimationDown.addFrame(sf::IntRect(128 * 2, 128 * 6, 128, 128));
		_stanceAnimationDown.addFrame(sf::IntRect(128 * 3, 128 * 6, 128, 128));
		_stanceAnimationLeft.setSpriteSheet(*_textureBody);
		_stanceAnimationLeft.addFrame(sf::IntRect(128 * 0, 128 * 0, 128, 128));
		_stanceAnimationLeft.addFrame(sf::IntRect(128 * 1, 128 * 0, 128, 128));
		_stanceAnimationLeft.addFrame(sf::IntRect(128 * 2, 128 * 0, 128, 128));
		_stanceAnimationLeft.addFrame(sf::IntRect(128 * 3, 128 * 0, 128, 128));
		_stanceAnimationRight.setSpriteSheet(*_textureBody);
		_stanceAnimationRight.addFrame(sf::IntRect(128 * 0, 128 * 4, 128, 128));
		_stanceAnimationRight.addFrame(sf::IntRect(128 * 1, 128 * 4, 128, 128));
		_stanceAnimationRight.addFrame(sf::IntRect(128 * 2, 128 * 4, 128, 128));
		_stanceAnimationRight.addFrame(sf::IntRect(128 * 3, 128 * 4, 128, 128));
		_stanceAnimationUp_Left.setSpriteSheet(*_textureBody);
		_stanceAnimationUp_Left.addFrame(sf::IntRect(128 * 0, 128 * 0, 128, 128));
		_stanceAnimationUp_Left.addFrame(sf::IntRect(128 * 1, 128 * 0, 128, 128));
		_stanceAnimationUp_Left.addFrame(sf::IntRect(128 * 2, 128 * 0, 128, 128));
		_stanceAnimationUp_Left.addFrame(sf::IntRect(128 * 3, 128 * 0, 128, 128));
		_stanceAnimationUp_Right.setSpriteSheet(*_textureBody);
		_stanceAnimationUp_Right.addFrame(sf::IntRect(128 * 0, 128 * 3, 128, 128));
		_stanceAnimationUp_Right.addFrame(sf::IntRect(128 * 1, 128 * 3, 128, 128));
		_stanceAnimationUp_Right.addFrame(sf::IntRect(128 * 2, 128 * 3, 128, 128));
		_stanceAnimationUp_Right.addFrame(sf::IntRect(128 * 3, 128 * 3, 128, 128));
		_stanceAnimationDown_Left.setSpriteSheet(*_textureBody);
		_stanceAnimationDown_Left.addFrame(sf::IntRect(128 * 0, 128 * 7, 128, 128));
		_stanceAnimationDown_Left.addFrame(sf::IntRect(128 * 1, 128 * 7, 128, 128));
		_stanceAnimationDown_Left.addFrame(sf::IntRect(128 * 2, 128 * 7, 128, 128));
		_stanceAnimationDown_Left.addFrame(sf::IntRect(128 * 3, 128 * 7, 128, 128));
		_stanceAnimationDown_Right.setSpriteSheet(*_textureBody);
		_stanceAnimationDown_Right.addFrame(sf::IntRect(128 * 0, 128 * 5, 128, 128));
		_stanceAnimationDown_Right.addFrame(sf::IntRect(128 * 1, 128 * 5, 128, 128));
		_stanceAnimationDown_Right.addFrame(sf::IntRect(128 * 2, 128 * 5, 128, 128));
		_stanceAnimationDown_Right.addFrame(sf::IntRect(128 * 3, 128 * 5, 128, 128));
	}

	// Running (8 frames)
	{
		_runningAnimationUp.setSpriteSheet(*_textureBody);
		_runningAnimationUp.addFrame(sf::IntRect(128 * 4, 128 * 2, 128, 128)); //Done
		_runningAnimationUp.addFrame(sf::IntRect(128 * 5, 128 * 2, 128, 128));
		_runningAnimationUp.addFrame(sf::IntRect(128 * 6, 128 * 2, 128, 128));
		_runningAnimationUp.addFrame(sf::IntRect(128 * 7, 128 * 2, 128, 128));
		_runningAnimationUp.addFrame(sf::IntRect(128 * 8, 128 * 2, 128, 128));
		_runningAnimationUp.addFrame(sf::IntRect(128 * 9, 128 * 2, 128, 128));
		_runningAnimationUp.addFrame(sf::IntRect(128 * 10, 128 * 2, 128, 128));
		_runningAnimationUp.addFrame(sf::IntRect(128 * 11, 128 * 2, 128, 128));
		_runningAnimationDown.setSpriteSheet(*_textureBody);
		_runningAnimationDown.addFrame(sf::IntRect(128 * 4, 128 * 6, 128, 128)); //Done
		_runningAnimationDown.addFrame(sf::IntRect(128 * 5, 128 * 6, 128, 128));
		_runningAnimationDown.addFrame(sf::IntRect(128 * 6, 128 * 6, 128, 128));
		_runningAnimationDown.addFrame(sf::IntRect(128 * 7, 128 * 6, 128, 128));
		_runningAnimationDown.addFrame(sf::IntRect(128 * 8, 128 * 6, 128, 128));
		_runningAnimationDown.addFrame(sf::IntRect(128 * 9, 128 * 6, 128, 128));
		_runningAnimationDown.addFrame(sf::IntRect(128 * 10, 128 * 6, 128, 128));
		_runningAnimationDown.addFrame(sf::IntRect(128 * 11, 128 * 6, 128, 128));
		_runningAnimationLeft.setSpriteSheet(*_textureBody);
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 4, 128 * 0, 128, 128)); //Done
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 5, 128 * 0, 128, 128));
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 6, 128 * 0, 128, 128));
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 7, 128 * 0, 128, 128));
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 8, 128 * 0, 128, 128));
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 9, 128 * 0, 128, 128));
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 10, 128 * 0, 128, 128));
		_runningAnimationLeft.addFrame(sf::IntRect(128 * 11, 128 * 0, 128, 128));
		_runningAnimationRight.setSpriteSheet(*_textureBody);
		_runningAnimationRight.addFrame(sf::IntRect(128 * 4, 128 * 4, 128, 128)); //Done
		_runningAnimationRight.addFrame(sf::IntRect(128 * 5, 128 * 4, 128, 128));
		_runningAnimationRight.addFrame(sf::IntRect(128 * 6, 128 * 4, 128, 128));
		_runningAnimationRight.addFrame(sf::IntRect(128 * 7, 128 * 4, 128, 128));
		_runningAnimationRight.addFrame(sf::IntRect(128 * 8, 128 * 4, 128, 128));
		_runningAnimationRight.addFrame(sf::IntRect(128 * 9, 128 * 4, 128, 128));
		_runningAnimationRight.addFrame(sf::IntRect(128 * 10, 128 * 4, 128, 128));
		_runningAnimationRight.addFrame(sf::IntRect(128 * 11, 128 * 4, 128, 128));
		_runningAnimationUp_Left.setSpriteSheet(*_textureBody);
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 4, 128 * 1, 128, 128)); //DONE
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 5, 128 * 1, 128, 128));
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 6, 128 * 1, 128, 128));
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 7, 128 * 1, 128, 128));
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 8, 128 * 1, 128, 128));
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 9, 128 * 1, 128, 128));
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 10, 128 * 1, 128, 128));
		_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 11, 128 * 1, 128, 128));
		_runningAnimationUp_Right.setSpriteSheet(*_textureBody);
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 4, 128 * 3, 128, 128)); //Done
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 5, 128 * 3, 128, 128));
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 6, 128 * 3, 128, 128));
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 7, 128 * 3, 128, 128));
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 8, 128 * 3, 128, 128));
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 9, 128 * 3, 128, 128));
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 10, 128 * 3, 128, 128));
		_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 11, 128 * 3, 128, 128));
		_runningAnimationDown_Left.setSpriteSheet(*_textureBody);
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 4, 128 * 7, 128, 128)); //Done
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 5, 128 * 7, 128, 128));
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 6, 128 * 7, 128, 128));
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 7, 128 * 7, 128, 128));
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 8, 128 * 7, 128, 128));
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 9, 128 * 7, 128, 128));
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 10, 128 * 7, 128, 128));
		_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 11, 128 * 7, 128, 128));
		_runningAnimationDown_Right.setSpriteSheet(*_textureBody);
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 4, 128 * 5, 128, 128)); //Done
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 5, 128 * 5, 128, 128));
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 6, 128 * 5, 128, 128));
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 7, 128 * 5, 128, 128));
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 8, 128 * 5, 128, 128));
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 9, 128 * 5, 128, 128));
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 10, 128 * 5, 128, 128));
		_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 11, 128 * 5, 128, 128));
	}
	// Melee Swing (4 frames)

	// Block (2 frames)

	// Hit and Die (6 frames)

	// Cast Spell (4 frames)

	// Shoot Bow (4 frames)
}

void Player::initHeadTextures()
{
	// Stance (4 frames)
	{
		_Head_stanceAnimationUp.setSpriteSheet(*_textureHead);
		_Head_stanceAnimationUp.addFrame(sf::IntRect(128 * 0, 128 * 2, 128, 128));
		_Head_stanceAnimationUp.addFrame(sf::IntRect(128 * 1, 128 * 2, 128, 128));
		_Head_stanceAnimationUp.addFrame(sf::IntRect(128 * 2, 128 * 2, 128, 128));
		_Head_stanceAnimationUp.addFrame(sf::IntRect(128 * 3, 128 * 2, 128, 128));
		_Head_stanceAnimationDown.setSpriteSheet(*_textureHead);
		_Head_stanceAnimationDown.addFrame(sf::IntRect(128 * 0, 128 * 6, 128, 128));
		_Head_stanceAnimationDown.addFrame(sf::IntRect(128 * 1, 128 * 6, 128, 128));
		_Head_stanceAnimationDown.addFrame(sf::IntRect(128 * 2, 128 * 6, 128, 128));
		_Head_stanceAnimationDown.addFrame(sf::IntRect(128 * 3, 128 * 6, 128, 128));
		_Head_stanceAnimationLeft.setSpriteSheet(*_textureHead);
		_Head_stanceAnimationLeft.addFrame(sf::IntRect(128 * 0, 128 * 0, 128, 128));
		_Head_stanceAnimationLeft.addFrame(sf::IntRect(128 * 1, 128 * 0, 128, 128));
		_Head_stanceAnimationLeft.addFrame(sf::IntRect(128 * 2, 128 * 0, 128, 128));
		_Head_stanceAnimationLeft.addFrame(sf::IntRect(128 * 3, 128 * 0, 128, 128));
		_Head_stanceAnimationRight.setSpriteSheet(*_textureHead);
		_Head_stanceAnimationRight.addFrame(sf::IntRect(128 * 0, 128 * 4, 128, 128));
		_Head_stanceAnimationRight.addFrame(sf::IntRect(128 * 1, 128 * 4, 128, 128));
		_Head_stanceAnimationRight.addFrame(sf::IntRect(128 * 2, 128 * 4, 128, 128));
		_Head_stanceAnimationRight.addFrame(sf::IntRect(128 * 3, 128 * 4, 128, 128));
		_Head_stanceAnimationUp_Left.setSpriteSheet(*_textureHead);
		_Head_stanceAnimationUp_Left.addFrame(sf::IntRect(128 * 0, 128 * 0, 128, 128));
		_Head_stanceAnimationUp_Left.addFrame(sf::IntRect(128 * 1, 128 * 0, 128, 128));
		_Head_stanceAnimationUp_Left.addFrame(sf::IntRect(128 * 2, 128 * 0, 128, 128));
		_Head_stanceAnimationUp_Left.addFrame(sf::IntRect(128 * 3, 128 * 0, 128, 128));
		_Head_stanceAnimationUp_Right.setSpriteSheet(*_textureHead);
		_Head_stanceAnimationUp_Right.addFrame(sf::IntRect(128 * 0, 128 * 3, 128, 128));
		_Head_stanceAnimationUp_Right.addFrame(sf::IntRect(128 * 1, 128 * 3, 128, 128));
		_Head_stanceAnimationUp_Right.addFrame(sf::IntRect(128 * 2, 128 * 3, 128, 128));
		_Head_stanceAnimationUp_Right.addFrame(sf::IntRect(128 * 3, 128 * 3, 128, 128));
		_Head_stanceAnimationDown_Left.setSpriteSheet(*_textureHead);
		_Head_stanceAnimationDown_Left.addFrame(sf::IntRect(128 * 0, 128 * 7, 128, 128));
		_Head_stanceAnimationDown_Left.addFrame(sf::IntRect(128 * 1, 128 * 7, 128, 128));
		_Head_stanceAnimationDown_Left.addFrame(sf::IntRect(128 * 2, 128 * 7, 128, 128));
		_Head_stanceAnimationDown_Left.addFrame(sf::IntRect(128 * 3, 128 * 7, 128, 128));
		_Head_stanceAnimationDown_Right.setSpriteSheet(*_textureHead);
		_Head_stanceAnimationDown_Right.addFrame(sf::IntRect(128 * 0, 128 * 5, 128, 128));
		_Head_stanceAnimationDown_Right.addFrame(sf::IntRect(128 * 1, 128 * 5, 128, 128));
		_Head_stanceAnimationDown_Right.addFrame(sf::IntRect(128 * 2, 128 * 5, 128, 128));
		_Head_stanceAnimationDown_Right.addFrame(sf::IntRect(128 * 3, 128 * 5, 128, 128));
	}

	// Running (8 frames)
	{
		_Head_runningAnimationUp.setSpriteSheet(*_textureHead);
		_Head_runningAnimationUp.addFrame(sf::IntRect(128 * 4, 128 * 2, 128, 128)); //Done
		_Head_runningAnimationUp.addFrame(sf::IntRect(128 * 5, 128 * 2, 128, 128));
		_Head_runningAnimationUp.addFrame(sf::IntRect(128 * 6, 128 * 2, 128, 128));
		_Head_runningAnimationUp.addFrame(sf::IntRect(128 * 7, 128 * 2, 128, 128));
		_Head_runningAnimationUp.addFrame(sf::IntRect(128 * 8, 128 * 2, 128, 128));
		_Head_runningAnimationUp.addFrame(sf::IntRect(128 * 9, 128 * 2, 128, 128));
		_Head_runningAnimationUp.addFrame(sf::IntRect(128 * 10, 128 * 2, 128, 128));
		_Head_runningAnimationUp.addFrame(sf::IntRect(128 * 11, 128 * 2, 128, 128));
		_Head_runningAnimationDown.setSpriteSheet(*_textureHead);
		_Head_runningAnimationDown.addFrame(sf::IntRect(128 * 4, 128 * 6, 128, 128)); //Done
		_Head_runningAnimationDown.addFrame(sf::IntRect(128 * 5, 128 * 6, 128, 128));
		_Head_runningAnimationDown.addFrame(sf::IntRect(128 * 6, 128 * 6, 128, 128));
		_Head_runningAnimationDown.addFrame(sf::IntRect(128 * 7, 128 * 6, 128, 128));
		_Head_runningAnimationDown.addFrame(sf::IntRect(128 * 8, 128 * 6, 128, 128));
		_Head_runningAnimationDown.addFrame(sf::IntRect(128 * 9, 128 * 6, 128, 128));
		_Head_runningAnimationDown.addFrame(sf::IntRect(128 * 10, 128 * 6, 128, 128));
		_Head_runningAnimationDown.addFrame(sf::IntRect(128 * 11, 128 * 6, 128, 128));
		_Head_runningAnimationLeft.setSpriteSheet(*_textureHead);
		_Head_runningAnimationLeft.addFrame(sf::IntRect(128 * 4, 128 * 0, 128, 128)); //Done
		_Head_runningAnimationLeft.addFrame(sf::IntRect(128 * 5, 128 * 0, 128, 128));
		_Head_runningAnimationLeft.addFrame(sf::IntRect(128 * 6, 128 * 0, 128, 128));
		_Head_runningAnimationLeft.addFrame(sf::IntRect(128 * 7, 128 * 0, 128, 128));
		_Head_runningAnimationLeft.addFrame(sf::IntRect(128 * 8, 128 * 0, 128, 128));
		_Head_runningAnimationLeft.addFrame(sf::IntRect(128 * 9, 128 * 0, 128, 128));
		_Head_runningAnimationLeft.addFrame(sf::IntRect(128 * 10, 128 * 0, 128, 128));
		_Head_runningAnimationLeft.addFrame(sf::IntRect(128 * 11, 128 * 0, 128, 128));
		_Head_runningAnimationRight.setSpriteSheet(*_textureHead);
		_Head_runningAnimationRight.addFrame(sf::IntRect(128 * 4, 128 * 4, 128, 128)); //Done
		_Head_runningAnimationRight.addFrame(sf::IntRect(128 * 5, 128 * 4, 128, 128));
		_Head_runningAnimationRight.addFrame(sf::IntRect(128 * 6, 128 * 4, 128, 128));
		_Head_runningAnimationRight.addFrame(sf::IntRect(128 * 7, 128 * 4, 128, 128));
		_Head_runningAnimationRight.addFrame(sf::IntRect(128 * 8, 128 * 4, 128, 128));
		_Head_runningAnimationRight.addFrame(sf::IntRect(128 * 9, 128 * 4, 128, 128));
		_Head_runningAnimationRight.addFrame(sf::IntRect(128 * 10, 128 * 4, 128, 128));
		_Head_runningAnimationRight.addFrame(sf::IntRect(128 * 11, 128 * 4, 128, 128));
		_Head_runningAnimationUp_Left.setSpriteSheet(*_textureHead);
		_Head_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 4, 128 * 1, 128, 128)); //DONE
		_Head_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 5, 128 * 1, 128, 128));
		_Head_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 6, 128 * 1, 128, 128));
		_Head_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 7, 128 * 1, 128, 128));
		_Head_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 8, 128 * 1, 128, 128));
		_Head_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 9, 128 * 1, 128, 128));
		_Head_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 10, 128 * 1, 128, 128));
		_Head_runningAnimationUp_Left.addFrame(sf::IntRect(128 * 11, 128 * 1, 128, 128));
		_Head_runningAnimationUp_Right.setSpriteSheet(*_textureHead);
		_Head_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 4, 128 * 3, 128, 128)); //Done
		_Head_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 5, 128 * 3, 128, 128));
		_Head_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 6, 128 * 3, 128, 128));
		_Head_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 7, 128 * 3, 128, 128));
		_Head_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 8, 128 * 3, 128, 128));
		_Head_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 9, 128 * 3, 128, 128));
		_Head_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 10, 128 * 3, 128, 128));
		_Head_runningAnimationUp_Right.addFrame(sf::IntRect(128 * 11, 128 * 3, 128, 128));
		_Head_runningAnimationDown_Left.setSpriteSheet(*_textureHead);
		_Head_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 4, 128 * 7, 128, 128)); //Done
		_Head_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 5, 128 * 7, 128, 128));
		_Head_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 6, 128 * 7, 128, 128));
		_Head_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 7, 128 * 7, 128, 128));
		_Head_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 8, 128 * 7, 128, 128));
		_Head_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 9, 128 * 7, 128, 128));
		_Head_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 10, 128 * 7, 128, 128));
		_Head_runningAnimationDown_Left.addFrame(sf::IntRect(128 * 11, 128 * 7, 128, 128));
		_Head_runningAnimationDown_Right.setSpriteSheet(*_textureHead);
		_Head_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 4, 128 * 5, 128, 128)); //Done
		_Head_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 5, 128 * 5, 128, 128));
		_Head_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 6, 128 * 5, 128, 128));
		_Head_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 7, 128 * 5, 128, 128));
		_Head_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 8, 128 * 5, 128, 128));
		_Head_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 9, 128 * 5, 128, 128));
		_Head_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 10, 128 * 5, 128, 128));
		_Head_runningAnimationDown_Right.addFrame(sf::IntRect(128 * 11, 128 * 5, 128, 128));
	}
	// Melee Swing (4 frames)

	// Block (2 frames)

	// Hit and Die (6 frames)

	// Cast Spell (4 frames)

	// Shoot Bow (4 frames)
}

void Player::initWeaponTextures()
{
	// Stance (4 frames)

	// Running (8 frames)

	// Melee Swing (4 frames)

	// Block (2 frames)

	// Hit and Die (6 frames)

	// Cast Spell (4 frames)

	// Shoot Bow (4 frames)
}
