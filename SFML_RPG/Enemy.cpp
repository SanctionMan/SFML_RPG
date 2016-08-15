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
	//_bounds.move(movement * _deltaTime.asSeconds());
	_shape.move(movement * _deltaTime.asSeconds());
	
	// Update _positions and _body
	_position = _shape.getPosition();
	_animatedBody.setPosition(_position.x, _position.y);
	_bounds.setPosition(_position.x, _position.y);

	//// Update Animation
	_animatedBody.play(*_currentAnimationBody);
	_animatedBody.update(_deltaTime);

	// Set Animation State
	if (!_isMovingUp && !_isMovingDown && !_isMovingLeft && !_isMovingRight)
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
	if (_isMovingUp && _isMovingLeft)
	{
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationUp_Left;
		_lastAnimationState = _movingUp_Left;
	}
	if (_isMovingUp && _isMovingRight)
	{
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationUp_Right;
		_lastAnimationState = _movingUp_Right;
	}
	if (_isMovingDown && _isMovingLeft)
	{
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationDown_Left;
		_lastAnimationState = _movingDown_Left;
	}
	if (_isMovingDown && _isMovingRight)
	{
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_currentAnimationBody = &_runningAnimationDown_Right;
		_lastAnimationState = _movingDown_Right;
	}

	updateAI();

}

void Enemy::aiRender(sf::RenderWindow & _window)
{
	_window.draw(_bounds);
	_window.draw(_shape);
	_window.draw(_animatedBody);

}

void Enemy::aiProcessEvents(sf::Event & event)
{
	// Nothing at this point in time
}

void Enemy::updateAI()
{
	if (CalculateDistance(GetPlayer()->_position, _position) < 20)
	{
		cout << "Hit ya you slut!w" << endl;
	}

	//cout << "player X=" << GetPlayer()->_position.x << "player Y=" << GetPlayer()->_position.y << endl;
	//cout << "enemy X=" << _position.x << "enemy Y=" << _position.y << endl;
}

void Enemy::constructEnemy(sf::Vector2f position, sf::Vector2f animationSize, sf::Texture* texture)
{
	_position = position;
	_radius = 10;
	_mass = 1;
	_animationSize = animationSize;
	_textureBody = texture;

	// Setup collision bounds
	_bounds.setSize(sf::Vector2f(_animationSize.x / 4, _animationSize.y / 4));
	_bounds.setPosition(sf::Vector2f(_position.x, _position.y));
	_bounds.setOrigin(_bounds.getSize() / 2.f);
	_bounds.setOutlineThickness(1);
	_bounds.setOutlineColor(sf::Color::Green);
	_bounds.setFillColor(sf::Color(0, 0, 0, 0));

	_shape.setRadius(_radius);
	_shape.setPosition(_position.x, _position.y);
	_shape.setOrigin(sf::Vector2f(_radius / 2, _radius / 2));
	_shape.setOutlineThickness(1);
	_shape.setOutlineColor(sf::Color::Green);
	_shape.setFillColor(sf::Color(0, 0, 0, 0));
}

void Enemy::initEnemyTextures()
{
	cout << "123123" << endl;
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
	_animatedBody.setPosition(_position);
	_animatedBody.setOrigin(sf::Vector2f(_animationSize.x / 2, _animationSize.y / 2));
}
