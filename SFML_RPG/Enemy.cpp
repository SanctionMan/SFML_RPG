#include "Enemy.h"



Enemy::Enemy():
	_textureBody(NULL),
	_animatedBody(sf::seconds(0.2f), true, false)
{

}


Enemy::~Enemy()
{
}

void Enemy::aiUpdate(sf::Time _deltaTime)
{
	// Update Health Bar
	_healthBar.setPosition(_position);
	_healthBar.setCurrentHealth(_health);
	_healthBar.setMaxHealth(_maxHealth);
	_healthBar.setCurrentMana(_mana);
	_healthBar.setMaxMana(_maxMana);
	_healthBar.update(_deltaTime);
	
	// Update _positions and _body
	_position = _bounds.getPosition();
	_animatedBody.setPosition(_position + _adjustment_xy);

	// Update Animation
	_animatedBody.play(*_currentAnimationBody);
	_animatedBody.update(_deltaTime);

	// Set Animation State
	if (!_isMoving)
	{
		switch (_lastAnimationState)
		{
		case _movingUp:
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationUp;
			break;
		case _movingDown:
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationDown;
			break;
		case _movingLeft:
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationLeft;
			break;
		case _movingRight:
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationRight;
			break;
		case _movingUp_Left:
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationUp_Left;
			break;
		case _movingUp_Right:
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationUp_Right;
			break;
		case _movingDown_Left:
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationDown_Left;
			break;
		case _movingDown_Right:
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_currentAnimationBody = &_stanceAnimationDown_Right;
			break;
		}

	}
	if (_isMovingUp)
	{
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationUp;
		_lastAnimationState = _movingUp;
	}
	if (_isMovingDown)
	{
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationDown;
		_lastAnimationState = _movingDown;
	}
	if (_isMovingLeft)
	{
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationLeft;
		_lastAnimationState = _movingLeft;
	}
	if (_isMovingRight)
	{
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationRight;
		_lastAnimationState = _movingRight;
	}
	if (_isMovingUp_Left)
	{
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationUp_Left;
		_lastAnimationState = _movingUp_Left;
	}
	if (_isMovingUp_Right)
	{
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationUp_Right;
		_lastAnimationState = _movingUp_Right;
	}
	if (_isMovingDown_Left)
	{
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationDown_Left;
		_lastAnimationState = _movingDown_Left;
	}
	if (_isMovingDown_Right)
	{
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationDown_Right;
		_lastAnimationState = _movingDown_Right;
	}
	
	// Update Movement
	updateAI(_deltaTime);
}

void Enemy::aiRender(sf::RenderWindow & _window)
{
	if (_drawBounds)
	{
		_window.draw(_bounds);
	}
	_healthBar.render(_window);
	_window.draw(_animatedBody);
}

void Enemy::aiProcessEvents(sf::Event & event)
{
	entityEvents(event);
}

void Enemy::updateAI(sf::Time _deltaTime)
{
	// Calculations to get Player
	const float  PI_F = 3.14159265358979f;
	float _distance = CalculateDistance(GetPlayer()->_position, _position);
	sf::Vector2f _direction = (GetPlayer()->_position - _position);
	sf::Vector2f _unitVector = sf::Vector2f(_direction.x / _distance, _direction.y / _distance);

	float _angle = atan2(GetPlayer()->_position.y - _position.y, GetPlayer()->_position.x - _position.x);
	_angle = (_angle * 180) / PI_F;

	// Move enemy to Player
	if (_distance < 200 && _distance > 50)
	{
		_bounds.move(_unitVector * _enemySpeed * _deltaTime.asSeconds());
		_isMoving = true;
	}
	else {
		_isMoving = false;
	}

	// Set Facing Angle
	{
		// Up
		if (_angle > -112.5 && _angle < -67.5 && _isMoving)
			_isMovingUp = true;
		else
			_isMovingUp = false;
		// Down
		if (_angle > 67.5 && _angle < 112.5 && _isMoving)
			_isMovingDown = true;
		else
			_isMovingDown = false;
		// Left
		if (_angle > 157.5  && _isMoving || _angle < -157.5 && _isMoving)
			_isMovingLeft = true;
		else
			_isMovingLeft = false;
		// Right
		if (_angle > -22.5 && _angle < 22.5 && _isMoving)
			_isMovingRight = true;
		else
			_isMovingRight = false;
		// Up Left
		if (_angle < -112.5 && _angle > -157.5 && _isMoving)
			_isMovingUp_Left = true;
		else
			_isMovingUp_Left = false;
		// Up Right
		if (_angle < -22.5 && _angle > -67.5 && _isMoving)
			_isMovingUp_Right = true;
		else
			_isMovingUp_Right = false;
		// Down Left
		if (_angle > 112.5 && _angle < 157.5 && _isMoving)
			_isMovingDown_Left = true;
		else
			_isMovingDown_Left = false;
		// Down Right
		if (_angle > 22.5 && _angle < 67.5 && _isMoving)
			_isMovingDown_Right = true;
		else
			_isMovingDown_Right = false;
	}

}		

void Enemy::constructEnemy(sf::Vector2f position, sf::Vector2f animationSize, sf::Texture* texture)
{
	_position = position;
	_radius = 10;
	_mass = 1;
	_animationSize = animationSize;
	_textureBody = texture;
	_adjustment_xy = sf::Vector2f(0.f, -30.f);

	_healthBar.setAdjustment(sf::Vector2f(0, -50));

	// Setup collision bounds

	_bounds.setRadius(_radius);
	_bounds.setPosition(_position);
	_bounds.setOrigin(sf::Vector2f(_radius, _radius));
	_bounds.setOutlineThickness(2);
	_bounds.setOutlineColor(sf::Color::Red);
	_bounds.setFillColor(sf::Color::Transparent);
	//_bounds.scale(1.f, 0.55f);
}

void Enemy::initEnemyTextures()
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

	// Create pointer to current animation
	_currentAnimationBody = &_stanceAnimationDown;

	// Setup animatedsprite
	_animatedBody.setPosition(_position + _adjustment_xy);
	_animatedBody.setOrigin(sf::Vector2f(_animationSize.x / 2, _animationSize.y / 2));
}
