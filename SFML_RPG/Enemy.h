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

	void aiUpdate(sf::Time _deltaTime);
	void aiRender(sf::RenderWindow &_window);
	void aiProcessEvents(sf::Event &event);
	
	virtual void render(sf::RenderWindow &_window) = 0;
	virtual void update(sf::Time _deltaTime) = 0;

	void updateAI(sf::Time _deltaTime);
	void constructEnemy(sf::Vector2f position, sf::Vector2f animationSize, sf::Texture* texture);
		
	void initEnemyTextures();

public:

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

	float _enemySpeed = 150;

	HealthBar _healthBar;

	bool _isMovingUp = false;
	bool _isMovingDown = false;
	bool _isMovingLeft = false;
	bool _isMovingRight = false;


	enum animationEnum
	{
		_movingUp = 1,
		_movingDown = 2,
		_movingLeft = 3,
		_movingRight = 4,
		_movingUp_Left = 5,
		_movingUp_Right = 6,
		_movingDown_Left = 7,
		_movingDown_Right = 8,
	};

	animationEnum _lastAnimationState;

	sf::Texture* _textureBody;
	sf::Vector2f _animationSize;

	Animation* _currentAnimationBody;

	AnimatedSprite _animatedBody;

	Animation _stanceAnimationUp;
	Animation _stanceAnimationDown;
	Animation _stanceAnimationLeft;
	Animation _stanceAnimationRight;
	Animation _stanceAnimationUp_Left;
	Animation _stanceAnimationUp_Right;
	Animation _stanceAnimationDown_Left;
	Animation _stanceAnimationDown_Right;

	Animation _runningAnimationUp;
	Animation _runningAnimationDown;
	Animation _runningAnimationLeft;
	Animation _runningAnimationRight;
	Animation _runningAnimationUp_Left;
	Animation _runningAnimationUp_Right;
	Animation _runningAnimationDown_Left;
	Animation _runningAnimationDown_Right;

};

#include "Goblin.h"