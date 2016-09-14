#pragma once
#include <math.h>
#include "Game.h"
#include "AnimatedSprite.h"
#include "HealthBar.h"

class Enemy : public Entity
{
public:
	Enemy();
	~Enemy();

	void enemyUpdate(sf::Time _deltaTime);
	void enemyRender(sf::RenderWindow &_window);
	void enemyProcessEvents(sf::Event &event);
	
	virtual void render(sf::RenderWindow &_window) = 0;
	virtual void update(sf::Time _deltaTime) = 0;

	void enemyAI(sf::Time _deltaTime);
	void constructEnemy(sf::Vector2f position, sf::Vector2f animationSize, 
						sf::Texture* texture, sf::Vector2f adjustment_xy);
	

public:
	HealthBar _healthBar;
	// Stats
	int _level = 1;

	float _maxHealth = 100;
	float _maxMana = 100;
	float _health = 100;
	float _mana = 100;

	int _physical = 1;
	int _mental = 1;
	int _offense = 1;
	int _defense = 1;

	// AI stats
	float _AggroRange = 300;
	float _distance;

	// Enemy Actions
	bool _isAggro = false;


	bool _isStanding = false;
	bool _isRunning = false;
	bool _isAttacking = false;
	bool _isCharging = false;
	bool _isCasting = false;
	bool _isShooting = false;
	bool _isBlocking = false;
	bool _isTakingHit = false;
	bool _isDying = false;

	// Enemy movement
	bool _isMoving = false;
	bool _isMovingUp = false;
	bool _isMovingDown = false;
	bool _isMovingLeft = false;
	bool _isMovingRight = false;
	bool _isMovingUp_Right = false;
	bool _isMovingUp_Left = false;
	bool _isMovingDown_Left = false;
	bool _isMovingDown_Right = false;

	float _speed = 150;

	enum Direction
	{
		Up = 2,
		Down = 6,
		Left = 0,
		Right = 4,
		Up_Left = 1,
		Up_Right = 3,
		Down_Left = 7,
		Down_Right = 5,
	};

	enum AI_States
	{
		Wander = 0,
		Chase = 1,
		Attack = 2,
		Runaway = 3,
	};

	// Last Animation Direction;
	Direction _lastAnimationDirection;

	// Textures pointer
	sf::Texture* _textureBody;

	// Animation sprites
	AnimatedSprite _animatedBody;

	// Animation size
	sf::Vector2f _animationSize;

	// Animation pointer
	Animation* _currentAnimationBody;

	// Animation map<>
	map<string, Animation> _Animations;
};

#include "Goblin.h"