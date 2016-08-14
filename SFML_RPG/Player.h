#pragma once
#include "Entity.h"
#include "Game.h"
#include "AnimatedSprite.h"

class Player : public Entity
{
public:
	Player(sf::Vector2f position, sf::Texture* headTexture, sf::Texture* bodyTexture);
	~Player();

	void update(sf::Time _deltaTime);
	void render(sf::RenderWindow &_window);
	void processEvents(sf::Event &event);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void initPlayerTextures();

	void initBodyTextures();
	void initHeadTextures();
	void initWeaponTextures();


private:
	// Player movement
	bool _isMovingUp = false;
	bool _isMovingDown = false;
	bool _isMovingLeft = false;
	bool _isMovingRight = false;

	enum animationEnum
	{	_movingUp = 1,
		_movingDown = 2,
		_movingLeft = 3,
		_movingRight = 4,
		_movingUp_Left = 5,
		_movingUp_Right = 6,
		_movingDown_Left = 7,
		_movingDown_Right = 8,
	};

	struct AnimationState
	{

	};

	animationEnum _lastAnimationState;
	float _playerSpeed = 150;

	sf::Texture* _textureHead;
	sf::Texture* _textureBody;

	AnimatedSprite _animatedHead;
	AnimatedSprite _animatedBody;

	sf::Vector2f _animationSize;

	Animation* _currentAnimationBody;
	Animation* _currentAnimationHead;

	Animation _stanceAnimationUp;
	Animation _stanceAnimationDown;
	Animation _stanceAnimationLeft;
	Animation _stanceAnimationRight;
	Animation _stanceAnimationUp_Left;
	Animation _stanceAnimationUp_Right;
	Animation _stanceAnimationDown_Left;
	Animation _stanceAnimationDown_Right;
	Animation _Head_stanceAnimationUp;
	Animation _Head_stanceAnimationDown;
	Animation _Head_stanceAnimationLeft;
	Animation _Head_stanceAnimationRight;
	Animation _Head_stanceAnimationUp_Left;
	Animation _Head_stanceAnimationUp_Right;
	Animation _Head_stanceAnimationDown_Left;
	Animation _Head_stanceAnimationDown_Right;

	Animation _runningAnimationUp;
	Animation _runningAnimationDown;
	Animation _runningAnimationLeft;
	Animation _runningAnimationRight;
	Animation _runningAnimationUp_Left;
	Animation _runningAnimationUp_Right;
	Animation _runningAnimationDown_Left;
	Animation _runningAnimationDown_Right;
	Animation _Head_runningAnimationUp;
	Animation _Head_runningAnimationDown;
	Animation _Head_runningAnimationLeft;
	Animation _Head_runningAnimationRight;
	Animation _Head_runningAnimationUp_Left;
	Animation _Head_runningAnimationUp_Right;
	Animation _Head_runningAnimationDown_Left;
	Animation _Head_runningAnimationDown_Right;

};

