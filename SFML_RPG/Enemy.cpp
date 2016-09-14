#include "Enemy.h"



Enemy::Enemy():
	_textureBody(NULL),
	_animatedBody(sf::seconds(0.2f), true, false)
{

}


Enemy::~Enemy()
{
}

void Enemy::enemyUpdate(sf::Time _deltaTime)
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
	
	// Update enemyAI
	enemyAI(_deltaTime);
}

void Enemy::enemyRender(sf::RenderWindow & _window)
{
	if (_drawBounds)
	{
		_window.draw(_bounds);
	}
	//_healthBar.render(_window);
	_window.draw(_animatedBody);
}

void Enemy::enemyProcessEvents(sf::Event & event)
{
	entityEvents(event);
}

void Enemy::enemyAI(sf::Time _deltaTime)
{
	// Calculations to get Player
	_distance = CalculateDistance(GetPlayer()->_position, _position);
	sf::Vector2f _direction = (GetPlayer()->_position - _position);
	sf::Vector2f _unitVector = sf::Vector2f(_direction.x / _distance, _direction.y / _distance);
	// Calculate 360 degrees
	float _angle = atan2(GetPlayer()->_position.y - _position.y, GetPlayer()->_position.x - _position.x);
	_angle = (_angle * 180) / Pi;

	// Enemy Aggro
	if (_distance < _AggroRange)
	{
		_isAggro = true;
	}
	else {
		_isAggro = false;
	}


	// Set direction to player if he has aggro
	{
		// Up
		if (_angle > -112.5 && _angle < -67.5 && _isAggro)
			_lastAnimationDirection = Up;

		// Down
		if (_angle > 67.5 && _angle < 112.5 && _isAggro)
			_lastAnimationDirection = Down;

		// Left
		if (_angle > 157.5  && _isMoving || _angle < -157.5 && _isAggro)
			_lastAnimationDirection = Left;

		// Right
		if (_angle > -22.5 && _angle < 22.5 && _isAggro)
			_lastAnimationDirection = Right;

		// Up Left
		if (_angle < -112.5 && _angle > -157.5 && _isAggro)
			_lastAnimationDirection = Up_Left;

		// Up Right
		if (_angle < -22.5 && _angle > -67.5 && _isAggro)
			_lastAnimationDirection = Up_Right;

		// Down Left
		if (_angle > 112.5 && _angle < 157.5 && _isAggro)
			_lastAnimationDirection = Down_Left;

		// Down Right
		if (_angle > 22.5 && _angle < 67.5 && _isAggro)
			_lastAnimationDirection = Down_Right;
	}

	//Set Running
	if (_distance < _AggroRange && _distance > 50)
	{
		_isRunning = true;
		_bounds.move(_unitVector * _speed * _deltaTime.asSeconds());
	}
	else
		_isRunning = false;

	//Set Attacking
	if ( _distance <= 50)
	{
		_isAttacking = true;
	}
	else
		_isAttacking = false;
}		

void Enemy::constructEnemy(sf::Vector2f position, sf::Vector2f animationSize, 
	sf::Texture* texture, sf::Vector2f adjustment_xy)
{
	_position = position;
	_radius = 10;
	_mass = 1;
	_animationSize = animationSize;
	_textureBody = texture;
	_adjustment_xy = adjustment_xy;

	_animatedBody.setOrigin(sf::Vector2f(_animationSize.x / 2, _animationSize.y / 2));

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

