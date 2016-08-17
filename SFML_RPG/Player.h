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

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
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

	// Player movement
	bool _isCasting = false;
	bool _isAttacking = false;
	bool _isMovingUp = false;
	bool _isMovingDown = false;
	bool _isMovingLeft = false;
	bool _isMovingRight = false;

	float _playerSpeed = 150;

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
	// Last Animation State;
	animationEnum _lastAnimationState;
	// Textures
	sf::Texture* _textureHead;
	sf::Texture* _textureBody;
	sf::Texture* _textureWeapon;
	// Animation sprites
	AnimatedSprite _animatedHead;
	AnimatedSprite _animatedBody;
	AnimatedSprite _animatedWeapon;
	// Animation size
	sf::Vector2f _animationSize;
	// Animation pointers
	Animation* _currentAnimationBody;
	Animation* _currentAnimationHead;
	Animation* _currentAnimationWeapon;
	// Body Animations
	Animation _Body_Stance_AnimationUp;
	Animation _Body_Stance_AnimationDown;
	Animation _Body_Stance_AnimationLeft;
	Animation _Body_Stance_AnimationRight;
	Animation _Body_Stance_AnimationUp_Left;
	Animation _Body_Stance_AnimationUp_Right;
	Animation _Body_Stance_AnimationDown_Left;
	Animation _Body_Stance_AnimationDown_Right;
	Animation _Body_Running_AnimationUp;
	Animation _Body_Running_AnimationDown;
	Animation _Body_Running_AnimationLeft;
	Animation _Body_Running_AnimationRight;
	Animation _Body_Running_AnimationUp_Left;
	Animation _Body_Running_AnimationUp_Right;
	Animation _Body_Running_AnimationDown_Left;
	Animation _Body_Running_AnimationDown_Right;
	Animation _Body_MeleeSwing_AnimationUp;
	Animation _Body_MeleeSwing_AnimationDown;
	Animation _Body_MeleeSwing_AnimationLeft;
	Animation _Body_MeleeSwing_AnimationRight;
	Animation _Body_MeleeSwing_AnimationUp_Left;
	Animation _Body_MeleeSwing_AnimationUp_Right;
	Animation _Body_MeleeSwing_AnimationDown_Left;
	Animation _Body_MeleeSwing_AnimationDown_Right;
	Animation _Body_Block_AnimationUp;
	Animation _Body_Block_AnimationDown;
	Animation _Body_Block_AnimationLeft;
	Animation _Body_Block_AnimationRight;
	Animation _Body_Block_AnimationUp_Left;
	Animation _Body_Block_AnimationUp_Right;
	Animation _Body_Block_AnimationDown_Left;
	Animation _Body_Block_AnimationDown_Right;
	Animation _Body_HitDie_AnimationUp;
	Animation _Body_HitDie_AnimationDown;
	Animation _Body_HitDie_AnimationLeft;
	Animation _Body_HitDie_AnimationRight;
	Animation _Body_HitDie_AnimationUp_Left;
	Animation _Body_HitDie_AnimationUp_Right;
	Animation _Body_HitDie_AnimationDown_Left;
	Animation _Body_HitDie_AnimationDown_Right;
	Animation _Body_CastSpell_AnimationUp;
	Animation _Body_CastSpell_AnimationDown;
	Animation _Body_CastSpell_AnimationLeft;
	Animation _Body_CastSpell_AnimationRight;
	Animation _Body_CastSpell_AnimationUp_Left;
	Animation _Body_CastSpell_AnimationUp_Right;
	Animation _Body_CastSpell_AnimationDown_Left;
	Animation _Body_CastSpell_AnimationDown_Right;
	Animation _Body_ShootBow_AnimationUp;
	Animation _Body_ShootBow_AnimationDown;
	Animation _Body_ShootBow_AnimationLeft;
	Animation _Body_ShootBow_AnimationRight;
	Animation _Body_ShootBow_AnimationUp_Left;
	Animation _Body_ShootBow_AnimationUp_Right;
	Animation _Body_ShootBow_AnimationDown_Left;
	Animation _Body_ShootBow_AnimationDown_Right;

	// Head Animations
	Animation _Head_Stance_AnimationUp;
	Animation _Head_Stance_AnimationDown;
	Animation _Head_Stance_AnimationLeft;
	Animation _Head_Stance_AnimationRight;
	Animation _Head_Stance_AnimationUp_Left;
	Animation _Head_Stance_AnimationUp_Right;
	Animation _Head_Stance_AnimationDown_Left;
	Animation _Head_Stance_AnimationDown_Right;
	Animation _Head_Running_AnimationUp;
	Animation _Head_Running_AnimationDown;
	Animation _Head_Running_AnimationLeft;
	Animation _Head_Running_AnimationRight;
	Animation _Head_Running_AnimationUp_Left;
	Animation _Head_Running_AnimationUp_Right;
	Animation _Head_Running_AnimationDown_Left;
	Animation _Head_Running_AnimationDown_Right;
	Animation _Head_MeleeSwing_AnimationUp;
	Animation _Head_MeleeSwing_AnimationDown;
	Animation _Head_MeleeSwing_AnimationLeft;
	Animation _Head_MeleeSwing_AnimationRight;
	Animation _Head_MeleeSwing_AnimationUp_Left;
	Animation _Head_MeleeSwing_AnimationUp_Right;
	Animation _Head_MeleeSwing_AnimationDown_Left;
	Animation _Head_MeleeSwing_AnimationDown_Right;
	Animation _Head_Block_AnimationUp;
	Animation _Head_Block_AnimationDown;
	Animation _Head_Block_AnimationLeft;
	Animation _Head_Block_AnimationRight;
	Animation _Head_Block_AnimationUp_Left;
	Animation _Head_Block_AnimationUp_Right;
	Animation _Head_Block_AnimationDown_Left;
	Animation _Head_Block_AnimationDown_Right;
	Animation _Head_HitDie_AnimationUp;
	Animation _Head_HitDie_AnimationDown;
	Animation _Head_HitDie_AnimationLeft;
	Animation _Head_HitDie_AnimationRight;
	Animation _Head_HitDie_AnimationUp_Left;
	Animation _Head_HitDie_AnimationUp_Right;
	Animation _Head_HitDie_AnimationDown_Left;
	Animation _Head_HitDie_AnimationDown_Right;
	Animation _Head_CastSpell_AnimationUp;
	Animation _Head_CastSpell_AnimationDown;
	Animation _Head_CastSpell_AnimationLeft;
	Animation _Head_CastSpell_AnimationRight;
	Animation _Head_CastSpell_AnimationUp_Left;
	Animation _Head_CastSpell_AnimationUp_Right;
	Animation _Head_CastSpell_AnimationDown_Left;
	Animation _Head_CastSpell_AnimationDown_Right;
	Animation _Head_ShootBow_AnimationUp;
	Animation _Head_ShootBow_AnimationDown;
	Animation _Head_ShootBow_AnimationLeft;
	Animation _Head_ShootBow_AnimationRight;
	Animation _Head_ShootBow_AnimationUp_Left;
	Animation _Head_ShootBow_AnimationUp_Right;
	Animation _Head_ShootBow_AnimationDown_Left;
	Animation _Head_ShootBow_AnimationDown_Right;

	// Weapon Animation
	Animation _Weapon_Stance_AnimationUp;
	Animation _Weapon_Stance_AnimationDown;
	Animation _Weapon_Stance_AnimationLeft;
	Animation _Weapon_Stance_AnimationRight;
	Animation _Weapon_Stance_AnimationUp_Left;
	Animation _Weapon_Stance_AnimationUp_Right;
	Animation _Weapon_Stance_AnimationDown_Left;
	Animation _Weapon_Stance_AnimationDown_Right;
	Animation _Weapon_Running_AnimationUp;
	Animation _Weapon_Running_AnimationDown;
	Animation _Weapon_Running_AnimationLeft;
	Animation _Weapon_Running_AnimationRight;
	Animation _Weapon_Running_AnimationUp_Left;
	Animation _Weapon_Running_AnimationUp_Right;
	Animation _Weapon_Running_AnimationDown_Left;
	Animation _Weapon_Running_AnimationDown_Right;
	Animation _Weapon_MeleeSwing_AnimationUp;
	Animation _Weapon_MeleeSwing_AnimationDown;
	Animation _Weapon_MeleeSwing_AnimationLeft;
	Animation _Weapon_MeleeSwing_AnimationRight;
	Animation _Weapon_MeleeSwing_AnimationUp_Left;
	Animation _Weapon_MeleeSwing_AnimationUp_Right;
	Animation _Weapon_MeleeSwing_AnimationDown_Left;
	Animation _Weapon_MeleeSwing_AnimationDown_Right;
	Animation _Weapon_Block_AnimationUp;
	Animation _Weapon_Block_AnimationDown;
	Animation _Weapon_Block_AnimationLeft;
	Animation _Weapon_Block_AnimationRight;
	Animation _Weapon_Block_AnimationUp_Left;
	Animation _Weapon_Block_AnimationUp_Right;
	Animation _Weapon_Block_AnimationDown_Left;
	Animation _Weapon_Block_AnimationDown_Right;
	Animation _Weapon_HitDie_AnimationUp;
	Animation _Weapon_HitDie_AnimationDown;
	Animation _Weapon_HitDie_AnimationLeft;
	Animation _Weapon_HitDie_AnimationRight;
	Animation _Weapon_HitDie_AnimationUp_Left;
	Animation _Weapon_HitDie_AnimationUp_Right;
	Animation _Weapon_HitDie_AnimationDown_Left;
	Animation _Weapon_HitDie_AnimationDown_Right;
	Animation _Weapon_CastSpell_AnimationUp;
	Animation _Weapon_CastSpell_AnimationDown;
	Animation _Weapon_CastSpell_AnimationLeft;
	Animation _Weapon_CastSpell_AnimationRight;
	Animation _Weapon_CastSpell_AnimationUp_Left;
	Animation _Weapon_CastSpell_AnimationUp_Right;
	Animation _Weapon_CastSpell_AnimationDown_Left;
	Animation _Weapon_CastSpell_AnimationDown_Right;
	Animation _Weapon_ShootBow_AnimationUp;
	Animation _Weapon_ShootBow_AnimationDown;
	Animation _Weapon_ShootBow_AnimationLeft;
	Animation _Weapon_ShootBow_AnimationRight;
	Animation _Weapon_ShootBow_AnimationUp_Left;
	Animation _Weapon_ShootBow_AnimationUp_Right;
	Animation _Weapon_ShootBow_AnimationDown_Left;
	Animation _Weapon_ShootBow_AnimationDown_Right;

};

