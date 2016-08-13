#pragma once
#include "Entity.h"
#include "Game.h"
#include "AnimatedSprite.h"

class Player : public Entity
{
public:
	Player(sf::Texture* texture, sf::Vector2f position);
	~Player();

	void update(sf::Time _deltaTime);
	void render(sf::RenderWindow &_window);
	void processEvents(sf::Event &event);

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void initPlayerTextures();

private:
	// Player movement
	bool _isIdle = true;
	bool _isMovingUp = false;
	bool _isMovingDown = false;
	bool _isMovingLeft = false;
	bool _isMovingRight = false;

	float _playerSpeed = 200;

	//sf::Texture* _textureHead;
	sf::Texture* _textureBody;

	//AnimatedSprite _animatedHead;
	AnimatedSprite _animatedBody;

	Animation* _currentAnimation;

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

