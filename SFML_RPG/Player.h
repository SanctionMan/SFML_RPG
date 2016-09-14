#pragma once
#include "Entity.h"
#include "Game.h"
#include "AnimatedSprite.h"
#include  "HealthBar.h"

class Player : public Entity
{
public:
	Player(sf::Vector2f position, sf::Texture* headTexture, sf::Texture* bodyTexture, sf::Texture* weaponTexture);
	~Player();

	void update(sf::Time _deltaTime);
	void render(sf::RenderWindow &_window);
	void processEvents(sf::Event &event);

private:
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

	void setAnimationState();
	void setAnimations();

	void updateMovement(sf::Time _deltaTime);

	void initPlayerTextures();
	void initBodyTextures();
	void initHeadTextures();
	void initWeaponTextures();

private:
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

	HealthBar _healthBar;

	// Player Actions
	bool _isStanding = false;
	bool _isRunning = false;
	bool _isAttacking = false;
	bool _isCasting = false;
	bool _isShooting = false;
	bool _isBlocking = false;
	bool _isTakingHit = false;
	bool _isDying = false;

	bool _doingAttack = false;

	// Player movement
	bool _isMovingUp = false;
	bool _isMovingDown = false;
	bool _isMovingLeft = false;
	bool _isMovingRight = false;

	float _playerSpeed = 150;

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
	enum AnimationType
	{
		Standing = 0,
		Running = 4,
		Attacking = 12,
		Casting = 24,
		Shooting = 28,
		Blocking = 16,
		TakingHit = 18,
		Dying = 20,
	};

	// Last Animation State;
	Direction _lastAnimationDirection;
	AnimationType _ActionType;

	// Textures pointers
	sf::Texture* _textureHead;
	sf::Texture* _textureBody;
	sf::Texture* _textureWeapon;

	// Animation sprites
	AnimatedSprite _animatedHead;
	AnimatedSprite _animatedBody;
	AnimatedSprite _animatedWeapon;

	// Animation size
	sf::Vector2i _animationSize;

	// Animation pointers
	Animation* _currentAnimationBody;
	Animation* _currentAnimationHead;
	Animation* _currentAnimationWeapon;

	// Animation map<>
	map<string, Animation> _Animations;

};

