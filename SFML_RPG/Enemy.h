#pragma once
#include "Game.h"
#include "AnimatedSprite.h"

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

	void updateAI();
	void constructEnemy(sf::Vector2f position, sf::Vector2f animationSize, sf::Texture* texture);
		
	void initEnemyTextures();

public:

	bool _isMovingUp = false;
	bool _isMovingDown = false;
	bool _isMovingLeft = false;
	bool _isMovingRight = false;

	float _enemySpeed = 100;

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