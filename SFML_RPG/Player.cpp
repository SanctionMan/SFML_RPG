#include "Player.h"



Player::Player(sf::Vector2f position, sf::Texture* headTexture, sf::Texture* bodyTexture, sf::Texture* weaponTexture) :
	_textureHead(headTexture),
	_textureBody(bodyTexture),
	_textureWeapon(weaponTexture),
	_animatedHead(sf::seconds(0.2f), true, false),
	_animatedBody(sf::seconds(0.2f), true, false),
	_animatedWeapon(sf::seconds(0.2f), true, false),
	_animationSize(128, 128),
	_healthBar()
{
	//Set Variables
	_adjustment_xy = sf::Vector2f(0.f, -25.f);
	_position = position;
	_radius = 10;
	_mass = 5;

	//Set Healthbar
	_healthBar.setAdjustment(sf::Vector2f(0, -60));

	 // Setup collision bounds
	_bounds.setRadius(_radius);
	_bounds.setPosition(_position);
	_bounds.setOrigin(sf::Vector2f(_radius, _radius));
	_bounds.setOutlineThickness(2);
	_bounds.setOutlineColor(sf::Color::Red);
	_bounds.setFillColor(sf::Color(0, 0, 0, 0));
	//_bounds.scale(1.f, 0.55f);

	// Set entitie name
	_name = "Player";

	// Set player textures for animations
	initPlayerTextures();
	_animatedBody.setOrigin(sf::Vector2f(_animationSize.x / 2, _animationSize.y / 2));
	//_animatedBody.setScale(2, 2);
	_animatedHead.setOrigin(sf::Vector2f(_animationSize.x / 2, _animationSize.y / 2));
	//_animatedHead.setScale(2, 2);
	_animatedWeapon.setOrigin(sf::Vector2f(_animationSize.x / 2, _animationSize.y / 2));
	//_animatedWeapon.setScale(2, 2);
}

Player::~Player()
{
}

void Player::update(sf::Time _deltaTime)
{
	// Update Health Bar
	_healthBar.setPosition(_position);
	_healthBar.setCurrentHealth(_health);
	_healthBar.setMaxHealth(_maxHealth);
	_healthBar.setCurrentMana(_mana);
	_healthBar.setMaxMana(_maxMana);
	_healthBar.update(_deltaTime);

	// Update Movement
	sf::Vector2f movement(0.f, 0.f);
	if (_isMovingUp)
		movement.y -= _playerSpeed;
	if (_isMovingDown)
		movement.y += _playerSpeed;
	if (_isMovingLeft)
		movement.x -= _playerSpeed;
	if (_isMovingRight)
		movement.x += _playerSpeed;
	_bounds.move(movement * _deltaTime.asSeconds());

	// Update _positions and _body
	_position = _bounds.getPosition();
	_animatedBody.setPosition(_position + _adjustment_xy);
	_animatedHead.setPosition(_position + _adjustment_xy);
	_animatedWeapon.setPosition(_position + _adjustment_xy);

	// Update Animation
	_animatedHead.play(*_currentAnimationHead);
	_animatedHead.update(_deltaTime);
	_animatedBody.play(*_currentAnimationBody);
	_animatedBody.update(_deltaTime);
	_animatedWeapon.play(*_currentAnimationWeapon);
	_animatedWeapon.update(_deltaTime);

	// Set Animation State
	if (!_isMovingUp && !_isMovingDown && !_isMovingLeft && !_isMovingRight)
	{
		switch (_lastAnimationState)
		{
		case _movingUp:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_animatedWeapon.setFrameTime(sf::seconds(0.3f));
			_currentAnimationHead = &_Head_Stance_AnimationUp;
			_currentAnimationBody = &_Body_Stance_AnimationUp;
			_currentAnimationWeapon = &_Weapon_Stance_AnimationUp;
			break;
		case _movingDown:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_animatedWeapon.setFrameTime(sf::seconds(0.3f));
			_currentAnimationHead = &_Head_Stance_AnimationDown;
			_currentAnimationBody = &_Body_Stance_AnimationDown;
			_currentAnimationWeapon = &_Weapon_Stance_AnimationDown;
			break;
		case _movingLeft:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_animatedWeapon.setFrameTime(sf::seconds(0.3f));
			_currentAnimationHead = &_Head_Stance_AnimationLeft;
			_currentAnimationBody = &_Body_Stance_AnimationLeft;
			_currentAnimationWeapon = &_Weapon_Stance_AnimationLeft;
			break;
		case _movingRight:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_animatedWeapon.setFrameTime(sf::seconds(0.3f));
			_currentAnimationHead = &_Head_Stance_AnimationRight;
			_currentAnimationBody = &_Body_Stance_AnimationRight;
			_currentAnimationWeapon = &_Weapon_Stance_AnimationRight;
			break;
		case _movingUp_Left:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_animatedWeapon.setFrameTime(sf::seconds(0.3f));
			_currentAnimationHead = &_Head_Stance_AnimationUp_Left;
			_currentAnimationBody = &_Body_Stance_AnimationUp_Left;
			_currentAnimationWeapon = &_Weapon_Stance_AnimationUp_Left;
			break;
		case _movingUp_Right:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_animatedWeapon.setFrameTime(sf::seconds(0.3f));
			_currentAnimationHead = &_Head_Stance_AnimationUp_Right;
			_currentAnimationBody = &_Body_Stance_AnimationUp_Right;
			_currentAnimationWeapon = &_Weapon_Stance_AnimationUp_Right;
			break;
		case _movingDown_Left:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_animatedWeapon.setFrameTime(sf::seconds(0.3f));
			_currentAnimationHead = &_Head_Stance_AnimationDown_Left;
			_currentAnimationBody = &_Body_Stance_AnimationDown_Left;
			_currentAnimationWeapon = &_Weapon_Stance_AnimationDown_Left;
			break;
		case _movingDown_Right:
			_animatedHead.setFrameTime(sf::seconds(0.3f));
			_animatedBody.setFrameTime(sf::seconds(0.3f));
			_animatedWeapon.setFrameTime(sf::seconds(0.3f));
			_currentAnimationHead = &_Head_Stance_AnimationDown_Right;
			_currentAnimationBody = &_Body_Stance_AnimationDown_Right;
			_currentAnimationWeapon = &_Weapon_Stance_AnimationDown_Right;
			break;
		}
	
	}
	if (_isMovingUp)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_animatedWeapon.setFrameTime(sf::seconds(0.1f));
		_currentAnimationHead = &_Head_Running_AnimationUp;
		_currentAnimationBody = &_Body_Running_AnimationUp;
		_currentAnimationWeapon = &_Weapon_Running_AnimationUp;
		_lastAnimationState = _movingUp;
	}
	if (_isMovingDown)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_animatedWeapon.setFrameTime(sf::seconds(0.1f));
		_currentAnimationHead = &_Head_Running_AnimationDown;
		_currentAnimationBody = &_Body_Running_AnimationDown;
		_currentAnimationWeapon = &_Weapon_Running_AnimationDown;
		_lastAnimationState = _movingDown;
	}
	if (_isMovingLeft)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_animatedWeapon.setFrameTime(sf::seconds(0.1f));
		_currentAnimationHead = &_Head_Running_AnimationLeft;
		_currentAnimationBody = &_Body_Running_AnimationLeft;
		_currentAnimationWeapon = &_Weapon_Running_AnimationLeft;
		_lastAnimationState = _movingLeft;
	}
	if (_isMovingRight)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_animatedWeapon.setFrameTime(sf::seconds(0.1f));
		_currentAnimationHead = &_Head_Running_AnimationRight;
		_currentAnimationBody = &_Body_Running_AnimationRight;
		_currentAnimationWeapon = &_Weapon_Running_AnimationRight;
		_lastAnimationState = _movingRight;
	}
	if (_isMovingUp && _isMovingLeft)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_animatedWeapon.setFrameTime(sf::seconds(0.1f));
		_currentAnimationHead = &_Head_Running_AnimationUp_Left;
		_currentAnimationBody = &_Body_Running_AnimationUp_Left;
		_currentAnimationWeapon = &_Weapon_Running_AnimationUp_Left;
		_lastAnimationState = _movingUp_Left;
	}
	if (_isMovingUp && _isMovingRight)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_animatedWeapon.setFrameTime(sf::seconds(0.1f));
		_currentAnimationHead = &_Head_Running_AnimationUp_Right;
		_currentAnimationBody = &_Body_Running_AnimationUp_Right;
		_currentAnimationWeapon = &_Weapon_Running_AnimationUp_Right;
		_lastAnimationState = _movingUp_Right;
	}
	if (_isMovingDown && _isMovingLeft)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_animatedWeapon.setFrameTime(sf::seconds(0.1f));
		_currentAnimationHead = &_Head_Running_AnimationDown_Left;
		_currentAnimationBody = &_Body_Running_AnimationDown_Left;
		_currentAnimationWeapon = &_Weapon_Running_AnimationDown_Left;
		_lastAnimationState = _movingDown_Left;
	}
	if (_isMovingDown && _isMovingRight)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_animatedWeapon.setFrameTime(sf::seconds(0.1f));
		_currentAnimationHead = &_Head_Running_AnimationDown_Right;
		_currentAnimationBody = &_Body_Running_AnimationDown_Right;
		_currentAnimationWeapon = &_Weapon_Running_AnimationDown_Right;
		_lastAnimationState = _movingDown_Right;
	}
	if (_isAttacking)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_animatedWeapon.setFrameTime(sf::seconds(0.1f));
		_currentAnimationHead = &_Head_MeleeSwing_AnimationDown_Right;
		_currentAnimationBody = &_Body_MeleeSwing_AnimationDown_Right;
		_currentAnimationWeapon = &_Weapon_MeleeSwing_AnimationDown_Right;
	}
	if (_isCasting)
	{
		_animatedHead.setFrameTime(sf::seconds(0.1f));
		_animatedBody.setFrameTime(sf::seconds(0.1f));
		_animatedWeapon.setFrameTime(sf::seconds(0.1f));
		_currentAnimationHead = &_Head_CastSpell_AnimationDown_Right;
		_currentAnimationBody = &_Body_CastSpell_AnimationDown_Right;
		_currentAnimationWeapon = &_Weapon_CastSpell_AnimationDown_Right;
	}

}

void Player::render(sf::RenderWindow &_window)
{
	if (_drawBounds)
	{
		_window.draw(_bounds);
	}
	_window.draw(_animatedBody);
	_window.draw(_animatedHead);
	_window.draw(_animatedWeapon);

	//_healthBar.render(_window);
}

void Player::processEvents(sf::Event & event)
{
	entityEvents(event);
	switch (event.type)
	{
	case sf::Event::KeyPressed:
		handlePlayerInput(event.key.code, true);
		if (event.key.code == sf::Keyboard::Up)
			_health += 5;
		if (event.key.code == sf::Keyboard::Down)
			_health -= 5;
		if (event.key.code == sf::Keyboard::Left)
			_mana += 5;
		if (event.key.code == sf::Keyboard::Right)
			_mana -= 5;
		break;
	case sf::Event::KeyReleased:
		handlePlayerInput(event.key.code, false);
		break;
	}
}

void Player::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
	{
		_isMovingUp = isPressed;
	}
	else if (key == sf::Keyboard::S) 
	{
		_isMovingDown = isPressed;
	}
	else if (key == sf::Keyboard::A)
	{
		_isMovingLeft = isPressed;
	}
	else if (key == sf::Keyboard::D)
	{
		_isMovingRight = isPressed;
	}
	else if (key == sf::Keyboard::Space)
	{
	//	if (!_doingAttack) 
		//{
			_isAttacking = isPressed;
			_doingAttack = (_isAttacking == true) ? true : false; 
	//	}
	}
	else if (key == sf::Keyboard::R)
	{
		_isCasting = isPressed;
	}
}

void Player::initPlayerTextures()
{
	// Set textures for animations

	initHeadTextures();
	initBodyTextures();
	initWeaponTextures();

	// Create pointer to current animation
	_currentAnimationHead = &_Head_Stance_AnimationDown;
	_currentAnimationBody = &_Body_Stance_AnimationDown;

	// Setup animatedsprite
	//AnimatedSprite _animatedHead(sf::seconds(0.05), true, false);
	//AnimatedSprite _animatedBody(sf::seconds(0.05), true, false);
	_animatedHead.setPosition(_position + _adjustment_xy);
	_animatedBody.setPosition(_position + _adjustment_xy);
}

void Player::initBodyTextures()
{
	// Stance (4 frames)
	{	// Set texture for each animation
		_Animations["_Body_Stance_AnimationUp"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Stance_AnimationDown"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Stance_AnimationLeft"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Stance_AnimationRight"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Stance_AnimationUp_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Stance_AnimationUp_Right"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Stance_AnimationDown_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Stance_AnimationDown_Right"].setSpriteSheet(*_textureBody);
		for (int a= 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Body_Stance_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Body_Stance_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Body_Stance_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Stance_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Stance_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Stance_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Stance_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Stance_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Running (8 frames)
	{	// Set texture for each animation
		_Animations["_Body_Running_AnimationUp"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Running_AnimationDown"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Running_AnimationLeft"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Running_AnimationRight"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Running_AnimationUp_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Running_AnimationUp_Right"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Running_AnimationDown_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Running_AnimationDown_Right"].setSpriteSheet(*_textureBody);
		for (int a = 0; a < 8; a++)
		{	// Set each frame for animations
			_Animations["_Body_Running_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Body_Running_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Body_Running_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Running_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Running_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Running_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Running_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Running_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * a, _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Melee Swing (4 frames)
	{
		_Body_MeleeSwing_AnimationUp.setSpriteSheet(*_textureBody);
		_Body_MeleeSwing_AnimationUp.addFrame(sf::IntRect(128 * 12, 128 * 2, 128, 128));
		_Body_MeleeSwing_AnimationUp.addFrame(sf::IntRect(128 * 13, 128 * 2, 128, 128));
		_Body_MeleeSwing_AnimationUp.addFrame(sf::IntRect(128 * 14, 128 * 2, 128, 128));
		_Body_MeleeSwing_AnimationUp.addFrame(sf::IntRect(128 * 15, 128 * 2, 128, 128));
		_Body_MeleeSwing_AnimationDown.setSpriteSheet(*_textureBody);
		_Body_MeleeSwing_AnimationDown.addFrame(sf::IntRect(128 * 12, 128 * 6, 128, 128));
		_Body_MeleeSwing_AnimationDown.addFrame(sf::IntRect(128 * 13, 128 * 6, 128, 128));
		_Body_MeleeSwing_AnimationDown.addFrame(sf::IntRect(128 * 14, 128 * 6, 128, 128));
		_Body_MeleeSwing_AnimationDown.addFrame(sf::IntRect(128 * 15, 128 * 6, 128, 128));
		_Body_MeleeSwing_AnimationLeft.setSpriteSheet(*_textureBody);
		_Body_MeleeSwing_AnimationLeft.addFrame(sf::IntRect(128 * 12, 128 * 0, 128, 128));
		_Body_MeleeSwing_AnimationLeft.addFrame(sf::IntRect(128 * 13, 128 * 0, 128, 128));
		_Body_MeleeSwing_AnimationLeft.addFrame(sf::IntRect(128 * 14, 128 * 0, 128, 128));
		_Body_MeleeSwing_AnimationLeft.addFrame(sf::IntRect(128 * 15, 128 * 0, 128, 128));
		_Body_MeleeSwing_AnimationRight.setSpriteSheet(*_textureBody);
		_Body_MeleeSwing_AnimationRight.addFrame(sf::IntRect(128 * 12, 128 * 4, 128, 128));
		_Body_MeleeSwing_AnimationRight.addFrame(sf::IntRect(128 * 13, 128 * 4, 128, 128));
		_Body_MeleeSwing_AnimationRight.addFrame(sf::IntRect(128 * 14, 128 * 4, 128, 128));
		_Body_MeleeSwing_AnimationRight.addFrame(sf::IntRect(128 * 15, 128 * 4, 128, 128));
		_Body_MeleeSwing_AnimationUp_Left.setSpriteSheet(*_textureBody);
		_Body_MeleeSwing_AnimationUp_Left.addFrame(sf::IntRect(128 * 12, 128 * 1, 128, 128));
		_Body_MeleeSwing_AnimationUp_Left.addFrame(sf::IntRect(128 * 13, 128 * 1, 128, 128));
		_Body_MeleeSwing_AnimationUp_Left.addFrame(sf::IntRect(128 * 14, 128 * 1, 128, 128));
		_Body_MeleeSwing_AnimationUp_Left.addFrame(sf::IntRect(128 * 15, 128 * 1, 128, 128));
		_Body_MeleeSwing_AnimationUp_Right.setSpriteSheet(*_textureBody);
		_Body_MeleeSwing_AnimationUp_Right.addFrame(sf::IntRect(128 * 12, 128 * 3, 128, 128));
		_Body_MeleeSwing_AnimationUp_Right.addFrame(sf::IntRect(128 * 13, 128 * 3, 128, 128));
		_Body_MeleeSwing_AnimationUp_Right.addFrame(sf::IntRect(128 * 14, 128 * 3, 128, 128));
		_Body_MeleeSwing_AnimationUp_Right.addFrame(sf::IntRect(128 * 15, 128 * 3, 128, 128));
		_Body_MeleeSwing_AnimationDown_Left.setSpriteSheet(*_textureBody);
		_Body_MeleeSwing_AnimationDown_Left.addFrame(sf::IntRect(128 * 12, 128 * 7, 128, 128));
		_Body_MeleeSwing_AnimationDown_Left.addFrame(sf::IntRect(128 * 13, 128 * 7, 128, 128));
		_Body_MeleeSwing_AnimationDown_Left.addFrame(sf::IntRect(128 * 14, 128 * 7, 128, 128));
		_Body_MeleeSwing_AnimationDown_Left.addFrame(sf::IntRect(128 * 15, 128 * 7, 128, 128));
		_Body_MeleeSwing_AnimationDown_Right.setSpriteSheet(*_textureBody);
		_Body_MeleeSwing_AnimationDown_Right.addFrame(sf::IntRect(128 * 12, 128 * 5, 128, 128));
		_Body_MeleeSwing_AnimationDown_Right.addFrame(sf::IntRect(128 * 13, 128 * 5, 128, 128));
		_Body_MeleeSwing_AnimationDown_Right.addFrame(sf::IntRect(128 * 14, 128 * 5, 128, 128));
		_Body_MeleeSwing_AnimationDown_Right.addFrame(sf::IntRect(128 * 15, 128 * 5, 128, 128));
	}

	// Block (2 frames)
	{
		_Body_Block_AnimationUp.setSpriteSheet(*_textureBody);
		_Body_Block_AnimationUp.addFrame(sf::IntRect(128 * 16, 128 * 2, 128, 128));
		_Body_Block_AnimationUp.addFrame(sf::IntRect(128 * 17, 128 * 2, 128, 128));
		_Body_Block_AnimationDown.setSpriteSheet(*_textureBody);
		_Body_Block_AnimationDown.addFrame(sf::IntRect(128 * 16, 128 * 6, 128, 128));
		_Body_Block_AnimationDown.addFrame(sf::IntRect(128 * 17, 128 * 6, 128, 128));
		_Body_Block_AnimationLeft.setSpriteSheet(*_textureBody);
		_Body_Block_AnimationLeft.addFrame(sf::IntRect(128 * 16, 128 * 0, 128, 128));
		_Body_Block_AnimationLeft.addFrame(sf::IntRect(128 * 17, 128 * 0, 128, 128));
		_Body_Block_AnimationRight.setSpriteSheet(*_textureBody);
		_Body_Block_AnimationRight.addFrame(sf::IntRect(128 * 16, 128 * 4, 128, 128));
		_Body_Block_AnimationRight.addFrame(sf::IntRect(128 * 17, 128 * 4, 128, 128));
		_Body_Block_AnimationUp_Left.setSpriteSheet(*_textureBody);
		_Body_Block_AnimationUp_Left.addFrame(sf::IntRect(128 * 16, 128 * 1, 128, 128));
		_Body_Block_AnimationUp_Left.addFrame(sf::IntRect(128 * 17, 128 * 1, 128, 128));
		_Body_Block_AnimationUp_Right.setSpriteSheet(*_textureBody);
		_Body_Block_AnimationUp_Right.addFrame(sf::IntRect(128 * 16, 128 * 3, 128, 128));
		_Body_Block_AnimationUp_Right.addFrame(sf::IntRect(128 * 17, 128 * 3, 128, 128));
		_Body_Block_AnimationDown_Left.setSpriteSheet(*_textureBody);
		_Body_Block_AnimationDown_Left.addFrame(sf::IntRect(128 * 16, 128 * 7, 128, 128));
		_Body_Block_AnimationDown_Left.addFrame(sf::IntRect(128 * 17, 128 * 7, 128, 128));
		_Body_Block_AnimationDown_Right.setSpriteSheet(*_textureBody);
		_Body_Block_AnimationDown_Right.addFrame(sf::IntRect(128 * 16, 128 * 5, 128, 128));
		_Body_Block_AnimationDown_Right.addFrame(sf::IntRect(128 * 17, 128 * 5, 128, 128));
	}

	// Hit and Die (6 frames)
	{
		_Body_HitDie_AnimationUp.setSpriteSheet(*_textureBody);
		_Body_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 18, 128 * 2, 128, 128)); //Done
		_Body_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 19, 128 * 2, 128, 128));
		_Body_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 20, 128 * 2, 128, 128));
		_Body_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 21, 128 * 2, 128, 128));
		_Body_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 22, 128 * 2, 128, 128));
		_Body_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 23, 128 * 2, 128, 128));
		_Body_HitDie_AnimationDown.setSpriteSheet(*_textureBody);
		_Body_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 18, 128 * 6, 128, 128)); //Done
		_Body_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 19, 128 * 6, 128, 128));
		_Body_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 20, 128 * 6, 128, 128));
		_Body_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 21, 128 * 6, 128, 128));
		_Body_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 22, 128 * 6, 128, 128));
		_Body_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 23, 128 * 6, 128, 128));
		_Body_HitDie_AnimationLeft.setSpriteSheet(*_textureBody);
		_Body_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 18, 128 * 0, 128, 128)); //Done
		_Body_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 19, 128 * 0, 128, 128));
		_Body_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 20, 128 * 0, 128, 128));
		_Body_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 21, 128 * 0, 128, 128));
		_Body_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 22, 128 * 0, 128, 128));
		_Body_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 23, 128 * 0, 128, 128));
		_Body_HitDie_AnimationRight.setSpriteSheet(*_textureBody);
		_Body_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 18, 128 * 4, 128, 128)); //Done
		_Body_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 19, 128 * 4, 128, 128));
		_Body_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 20, 128 * 4, 128, 128));
		_Body_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 21, 128 * 4, 128, 128));
		_Body_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 22, 128 * 4, 128, 128));
		_Body_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 23, 128 * 4, 128, 128));
		_Body_HitDie_AnimationUp_Left.setSpriteSheet(*_textureBody);
		_Body_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 18, 128 * 1, 128, 128)); //DONE
		_Body_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 19, 128 * 1, 128, 128));
		_Body_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 20, 128 * 1, 128, 128));
		_Body_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 21, 128 * 1, 128, 128));
		_Body_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 22, 128 * 1, 128, 128));
		_Body_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 23, 128 * 1, 128, 128));
		_Body_HitDie_AnimationUp_Right.setSpriteSheet(*_textureBody);
		_Body_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 18, 128 * 3, 128, 128)); //Done
		_Body_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 19, 128 * 3, 128, 128));
		_Body_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 20, 128 * 3, 128, 128));
		_Body_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 21, 128 * 3, 128, 128));
		_Body_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 22, 128 * 3, 128, 128));
		_Body_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 23, 128 * 3, 128, 128));
		_Body_HitDie_AnimationDown_Left.setSpriteSheet(*_textureBody);
		_Body_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 18, 128 * 7, 128, 128)); //Done
		_Body_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 19, 128 * 7, 128, 128));
		_Body_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 20, 128 * 7, 128, 128));
		_Body_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 21, 128 * 7, 128, 128));
		_Body_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 22, 128 * 7, 128, 128));
		_Body_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 23, 128 * 7, 128, 128));
		_Body_HitDie_AnimationDown_Right.setSpriteSheet(*_textureBody);
		_Body_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 18, 128 * 5, 128, 128)); //Done
		_Body_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 19, 128 * 5, 128, 128));
		_Body_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 20, 128 * 5, 128, 128));
		_Body_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 21, 128 * 5, 128, 128));
		_Body_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 22, 128 * 5, 128, 128));
		_Body_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 23, 128 * 5, 128, 128));
	}

	// Cast Spell (4 frames)
	{
		_Body_CastSpell_AnimationUp.setSpriteSheet(*_textureBody);
		_Body_CastSpell_AnimationUp.addFrame(sf::IntRect(128 * 24, 128 * 2, 128, 128));
		_Body_CastSpell_AnimationUp.addFrame(sf::IntRect(128 * 25, 128 * 2, 128, 128));
		_Body_CastSpell_AnimationUp.addFrame(sf::IntRect(128 * 26, 128 * 2, 128, 128));
		_Body_CastSpell_AnimationUp.addFrame(sf::IntRect(128 * 27, 128 * 2, 128, 128));
		_Body_CastSpell_AnimationDown.setSpriteSheet(*_textureBody);
		_Body_CastSpell_AnimationDown.addFrame(sf::IntRect(128 * 24, 128 * 6, 128, 128));
		_Body_CastSpell_AnimationDown.addFrame(sf::IntRect(128 * 25, 128 * 6, 128, 128));
		_Body_CastSpell_AnimationDown.addFrame(sf::IntRect(128 * 26, 128 * 6, 128, 128));
		_Body_CastSpell_AnimationDown.addFrame(sf::IntRect(128 * 27, 128 * 6, 128, 128));
		_Body_CastSpell_AnimationLeft.setSpriteSheet(*_textureBody);
		_Body_CastSpell_AnimationLeft.addFrame(sf::IntRect(128 * 24, 128 * 0, 128, 128));
		_Body_CastSpell_AnimationLeft.addFrame(sf::IntRect(128 * 25, 128 * 0, 128, 128));
		_Body_CastSpell_AnimationLeft.addFrame(sf::IntRect(128 * 26, 128 * 0, 128, 128));
		_Body_CastSpell_AnimationLeft.addFrame(sf::IntRect(128 * 27, 128 * 0, 128, 128));
		_Body_CastSpell_AnimationRight.setSpriteSheet(*_textureBody);
		_Body_CastSpell_AnimationRight.addFrame(sf::IntRect(128 * 24, 128 * 4, 128, 128));
		_Body_CastSpell_AnimationRight.addFrame(sf::IntRect(128 * 25, 128 * 4, 128, 128));
		_Body_CastSpell_AnimationRight.addFrame(sf::IntRect(128 * 26, 128 * 4, 128, 128));
		_Body_CastSpell_AnimationRight.addFrame(sf::IntRect(128 * 27, 128 * 4, 128, 128));
		_Body_CastSpell_AnimationUp_Left.setSpriteSheet(*_textureBody);
		_Body_CastSpell_AnimationUp_Left.addFrame(sf::IntRect(128 * 24, 128 * 1, 128, 128));
		_Body_CastSpell_AnimationUp_Left.addFrame(sf::IntRect(128 * 25, 128 * 1, 128, 128));
		_Body_CastSpell_AnimationUp_Left.addFrame(sf::IntRect(128 * 26, 128 * 1, 128, 128));
		_Body_CastSpell_AnimationUp_Left.addFrame(sf::IntRect(128 * 27, 128 * 1, 128, 128));
		_Body_CastSpell_AnimationUp_Right.setSpriteSheet(*_textureBody);
		_Body_CastSpell_AnimationUp_Right.addFrame(sf::IntRect(128 * 24, 128 * 3, 128, 128));
		_Body_CastSpell_AnimationUp_Right.addFrame(sf::IntRect(128 * 25, 128 * 3, 128, 128));
		_Body_CastSpell_AnimationUp_Right.addFrame(sf::IntRect(128 * 26, 128 * 3, 128, 128));
		_Body_CastSpell_AnimationUp_Right.addFrame(sf::IntRect(128 * 27, 128 * 3, 128, 128));
		_Body_CastSpell_AnimationDown_Left.setSpriteSheet(*_textureBody);
		_Body_CastSpell_AnimationDown_Left.addFrame(sf::IntRect(128 * 24, 128 * 7, 128, 128));
		_Body_CastSpell_AnimationDown_Left.addFrame(sf::IntRect(128 * 25, 128 * 7, 128, 128));
		_Body_CastSpell_AnimationDown_Left.addFrame(sf::IntRect(128 * 26, 128 * 7, 128, 128));
		_Body_CastSpell_AnimationDown_Left.addFrame(sf::IntRect(128 * 27, 128 * 7, 128, 128));
		_Body_CastSpell_AnimationDown_Right.setSpriteSheet(*_textureBody);
		_Body_CastSpell_AnimationDown_Right.addFrame(sf::IntRect(128 * 24, 128 * 5, 128, 128));
		_Body_CastSpell_AnimationDown_Right.addFrame(sf::IntRect(128 * 25, 128 * 5, 128, 128));
		_Body_CastSpell_AnimationDown_Right.addFrame(sf::IntRect(128 * 26, 128 * 5, 128, 128));
		_Body_CastSpell_AnimationDown_Right.addFrame(sf::IntRect(128 * 27, 128 * 5, 128, 128));
	}

	// Shoot Bow (4 frames)
	{
		_Body_ShootBow_AnimationUp.setSpriteSheet(*_textureBody);
		_Body_ShootBow_AnimationUp.addFrame(sf::IntRect(128 * 28, 128 * 2, 128, 128));
		_Body_ShootBow_AnimationUp.addFrame(sf::IntRect(128 * 29, 128 * 2, 128, 128));
		_Body_ShootBow_AnimationUp.addFrame(sf::IntRect(128 * 30, 128 * 2, 128, 128));
		_Body_ShootBow_AnimationUp.addFrame(sf::IntRect(128 * 31, 128 * 2, 128, 128));
		_Body_ShootBow_AnimationDown.setSpriteSheet(*_textureBody);
		_Body_ShootBow_AnimationDown.addFrame(sf::IntRect(128 * 28, 128 * 6, 128, 128));
		_Body_ShootBow_AnimationDown.addFrame(sf::IntRect(128 * 29, 128 * 6, 128, 128));
		_Body_ShootBow_AnimationDown.addFrame(sf::IntRect(128 * 30, 128 * 6, 128, 128));
		_Body_ShootBow_AnimationDown.addFrame(sf::IntRect(128 * 31, 128 * 6, 128, 128));
		_Body_ShootBow_AnimationLeft.setSpriteSheet(*_textureBody);
		_Body_ShootBow_AnimationLeft.addFrame(sf::IntRect(128 * 28, 128 * 0, 128, 128));
		_Body_ShootBow_AnimationLeft.addFrame(sf::IntRect(128 * 29, 128 * 0, 128, 128));
		_Body_ShootBow_AnimationLeft.addFrame(sf::IntRect(128 * 30, 128 * 0, 128, 128));
		_Body_ShootBow_AnimationLeft.addFrame(sf::IntRect(128 * 31, 128 * 0, 128, 128));
		_Body_ShootBow_AnimationRight.setSpriteSheet(*_textureBody);
		_Body_ShootBow_AnimationRight.addFrame(sf::IntRect(128 * 28, 128 * 4, 128, 128));
		_Body_ShootBow_AnimationRight.addFrame(sf::IntRect(128 * 29, 128 * 4, 128, 128));
		_Body_ShootBow_AnimationRight.addFrame(sf::IntRect(128 * 30, 128 * 4, 128, 128));
		_Body_ShootBow_AnimationRight.addFrame(sf::IntRect(128 * 31, 128 * 4, 128, 128));
		_Body_ShootBow_AnimationUp_Left.setSpriteSheet(*_textureBody);
		_Body_ShootBow_AnimationUp_Left.addFrame(sf::IntRect(128 * 28, 128 * 1, 128, 128));
		_Body_ShootBow_AnimationUp_Left.addFrame(sf::IntRect(128 * 29, 128 * 1, 128, 128));
		_Body_ShootBow_AnimationUp_Left.addFrame(sf::IntRect(128 * 30, 128 * 1, 128, 128));
		_Body_ShootBow_AnimationUp_Left.addFrame(sf::IntRect(128 * 31, 128 * 1, 128, 128));
		_Body_ShootBow_AnimationUp_Right.setSpriteSheet(*_textureBody);
		_Body_ShootBow_AnimationUp_Right.addFrame(sf::IntRect(128 * 28, 128 * 3, 128, 128));
		_Body_ShootBow_AnimationUp_Right.addFrame(sf::IntRect(128 * 29, 128 * 3, 128, 128));
		_Body_ShootBow_AnimationUp_Right.addFrame(sf::IntRect(128 * 30, 128 * 3, 128, 128));
		_Body_ShootBow_AnimationUp_Right.addFrame(sf::IntRect(128 * 31, 128 * 3, 128, 128));
		_Body_ShootBow_AnimationDown_Left.setSpriteSheet(*_textureBody);
		_Body_ShootBow_AnimationDown_Left.addFrame(sf::IntRect(128 * 28, 128 * 7, 128, 128));
		_Body_ShootBow_AnimationDown_Left.addFrame(sf::IntRect(128 * 29, 128 * 7, 128, 128));
		_Body_ShootBow_AnimationDown_Left.addFrame(sf::IntRect(128 * 30, 128 * 7, 128, 128));
		_Body_ShootBow_AnimationDown_Left.addFrame(sf::IntRect(128 * 31, 128 * 7, 128, 128));
		_Body_ShootBow_AnimationDown_Right.setSpriteSheet(*_textureBody);
		_Body_ShootBow_AnimationDown_Right.addFrame(sf::IntRect(128 * 28, 128 * 5, 128, 128));
		_Body_ShootBow_AnimationDown_Right.addFrame(sf::IntRect(128 * 29, 128 * 5, 128, 128));
		_Body_ShootBow_AnimationDown_Right.addFrame(sf::IntRect(128 * 30, 128 * 5, 128, 128));
		_Body_ShootBow_AnimationDown_Right.addFrame(sf::IntRect(128 * 31, 128 * 5, 128, 128));
	}
}

void Player::initHeadTextures()
{
	// Stance (4 frames)
	{
		_Head_Stance_AnimationUp.setSpriteSheet(*_textureHead);
		_Head_Stance_AnimationUp.addFrame(sf::IntRect(128 * 0, 128 * 2, 128, 128));
		_Head_Stance_AnimationUp.addFrame(sf::IntRect(128 * 1, 128 * 2, 128, 128));
		_Head_Stance_AnimationUp.addFrame(sf::IntRect(128 * 2, 128 * 2, 128, 128));
		_Head_Stance_AnimationUp.addFrame(sf::IntRect(128 * 3, 128 * 2, 128, 128));
		_Head_Stance_AnimationDown.setSpriteSheet(*_textureHead);
		_Head_Stance_AnimationDown.addFrame(sf::IntRect(128 * 0, 128 * 6, 128, 128));
		_Head_Stance_AnimationDown.addFrame(sf::IntRect(128 * 1, 128 * 6, 128, 128));
		_Head_Stance_AnimationDown.addFrame(sf::IntRect(128 * 2, 128 * 6, 128, 128));
		_Head_Stance_AnimationDown.addFrame(sf::IntRect(128 * 3, 128 * 6, 128, 128));
		_Head_Stance_AnimationLeft.setSpriteSheet(*_textureHead);
		_Head_Stance_AnimationLeft.addFrame(sf::IntRect(128 * 0, 128 * 0, 128, 128));
		_Head_Stance_AnimationLeft.addFrame(sf::IntRect(128 * 1, 128 * 0, 128, 128));
		_Head_Stance_AnimationLeft.addFrame(sf::IntRect(128 * 2, 128 * 0, 128, 128));
		_Head_Stance_AnimationLeft.addFrame(sf::IntRect(128 * 3, 128 * 0, 128, 128));
		_Head_Stance_AnimationRight.setSpriteSheet(*_textureHead);
		_Head_Stance_AnimationRight.addFrame(sf::IntRect(128 * 0, 128 * 4, 128, 128));
		_Head_Stance_AnimationRight.addFrame(sf::IntRect(128 * 1, 128 * 4, 128, 128));
		_Head_Stance_AnimationRight.addFrame(sf::IntRect(128 * 2, 128 * 4, 128, 128));
		_Head_Stance_AnimationRight.addFrame(sf::IntRect(128 * 3, 128 * 4, 128, 128));
		_Head_Stance_AnimationUp_Left.setSpriteSheet(*_textureHead);
		_Head_Stance_AnimationUp_Left.addFrame(sf::IntRect(128 * 0, 128 * 0, 128, 128));
		_Head_Stance_AnimationUp_Left.addFrame(sf::IntRect(128 * 1, 128 * 0, 128, 128));
		_Head_Stance_AnimationUp_Left.addFrame(sf::IntRect(128 * 2, 128 * 0, 128, 128));
		_Head_Stance_AnimationUp_Left.addFrame(sf::IntRect(128 * 3, 128 * 0, 128, 128));
		_Head_Stance_AnimationUp_Right.setSpriteSheet(*_textureHead);
		_Head_Stance_AnimationUp_Right.addFrame(sf::IntRect(128 * 0, 128 * 3, 128, 128));
		_Head_Stance_AnimationUp_Right.addFrame(sf::IntRect(128 * 1, 128 * 3, 128, 128));
		_Head_Stance_AnimationUp_Right.addFrame(sf::IntRect(128 * 2, 128 * 3, 128, 128));
		_Head_Stance_AnimationUp_Right.addFrame(sf::IntRect(128 * 3, 128 * 3, 128, 128));
		_Head_Stance_AnimationDown_Left.setSpriteSheet(*_textureHead);
		_Head_Stance_AnimationDown_Left.addFrame(sf::IntRect(128 * 0, 128 * 7, 128, 128));
		_Head_Stance_AnimationDown_Left.addFrame(sf::IntRect(128 * 1, 128 * 7, 128, 128));
		_Head_Stance_AnimationDown_Left.addFrame(sf::IntRect(128 * 2, 128 * 7, 128, 128));
		_Head_Stance_AnimationDown_Left.addFrame(sf::IntRect(128 * 3, 128 * 7, 128, 128));
		_Head_Stance_AnimationDown_Right.setSpriteSheet(*_textureHead);
		_Head_Stance_AnimationDown_Right.addFrame(sf::IntRect(128 * 0, 128 * 5, 128, 128));
		_Head_Stance_AnimationDown_Right.addFrame(sf::IntRect(128 * 1, 128 * 5, 128, 128));
		_Head_Stance_AnimationDown_Right.addFrame(sf::IntRect(128 * 2, 128 * 5, 128, 128));
		_Head_Stance_AnimationDown_Right.addFrame(sf::IntRect(128 * 3, 128 * 5, 128, 128));
	}

	// Running (8 frames)
	{
		_Head_Running_AnimationUp.setSpriteSheet(*_textureHead);
		_Head_Running_AnimationUp.addFrame(sf::IntRect(128 * 4, 128 * 2, 128, 128)); //Done
		_Head_Running_AnimationUp.addFrame(sf::IntRect(128 * 5, 128 * 2, 128, 128));
		_Head_Running_AnimationUp.addFrame(sf::IntRect(128 * 6, 128 * 2, 128, 128));
		_Head_Running_AnimationUp.addFrame(sf::IntRect(128 * 7, 128 * 2, 128, 128));
		_Head_Running_AnimationUp.addFrame(sf::IntRect(128 * 8, 128 * 2, 128, 128));
		_Head_Running_AnimationUp.addFrame(sf::IntRect(128 * 9, 128 * 2, 128, 128));
		_Head_Running_AnimationUp.addFrame(sf::IntRect(128 * 10, 128 * 2, 128, 128));
		_Head_Running_AnimationUp.addFrame(sf::IntRect(128 * 11, 128 * 2, 128, 128));
		_Head_Running_AnimationDown.setSpriteSheet(*_textureHead);
		_Head_Running_AnimationDown.addFrame(sf::IntRect(128 * 4, 128 * 6, 128, 128)); //Done
		_Head_Running_AnimationDown.addFrame(sf::IntRect(128 * 5, 128 * 6, 128, 128));
		_Head_Running_AnimationDown.addFrame(sf::IntRect(128 * 6, 128 * 6, 128, 128));
		_Head_Running_AnimationDown.addFrame(sf::IntRect(128 * 7, 128 * 6, 128, 128));
		_Head_Running_AnimationDown.addFrame(sf::IntRect(128 * 8, 128 * 6, 128, 128));
		_Head_Running_AnimationDown.addFrame(sf::IntRect(128 * 9, 128 * 6, 128, 128));
		_Head_Running_AnimationDown.addFrame(sf::IntRect(128 * 10, 128 * 6, 128, 128));
		_Head_Running_AnimationDown.addFrame(sf::IntRect(128 * 11, 128 * 6, 128, 128));
		_Head_Running_AnimationLeft.setSpriteSheet(*_textureHead);
		_Head_Running_AnimationLeft.addFrame(sf::IntRect(128 * 4, 128 * 0, 128, 128)); //Done
		_Head_Running_AnimationLeft.addFrame(sf::IntRect(128 * 5, 128 * 0, 128, 128));
		_Head_Running_AnimationLeft.addFrame(sf::IntRect(128 * 6, 128 * 0, 128, 128));
		_Head_Running_AnimationLeft.addFrame(sf::IntRect(128 * 7, 128 * 0, 128, 128));
		_Head_Running_AnimationLeft.addFrame(sf::IntRect(128 * 8, 128 * 0, 128, 128));
		_Head_Running_AnimationLeft.addFrame(sf::IntRect(128 * 9, 128 * 0, 128, 128));
		_Head_Running_AnimationLeft.addFrame(sf::IntRect(128 * 10, 128 * 0, 128, 128));
		_Head_Running_AnimationLeft.addFrame(sf::IntRect(128 * 11, 128 * 0, 128, 128));
		_Head_Running_AnimationRight.setSpriteSheet(*_textureHead);
		_Head_Running_AnimationRight.addFrame(sf::IntRect(128 * 4, 128 * 4, 128, 128)); //Done
		_Head_Running_AnimationRight.addFrame(sf::IntRect(128 * 5, 128 * 4, 128, 128));
		_Head_Running_AnimationRight.addFrame(sf::IntRect(128 * 6, 128 * 4, 128, 128));
		_Head_Running_AnimationRight.addFrame(sf::IntRect(128 * 7, 128 * 4, 128, 128));
		_Head_Running_AnimationRight.addFrame(sf::IntRect(128 * 8, 128 * 4, 128, 128));
		_Head_Running_AnimationRight.addFrame(sf::IntRect(128 * 9, 128 * 4, 128, 128));
		_Head_Running_AnimationRight.addFrame(sf::IntRect(128 * 10, 128 * 4, 128, 128));
		_Head_Running_AnimationRight.addFrame(sf::IntRect(128 * 11, 128 * 4, 128, 128));
		_Head_Running_AnimationUp_Left.setSpriteSheet(*_textureHead);
		_Head_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 4, 128 * 1, 128, 128)); //DONE
		_Head_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 5, 128 * 1, 128, 128));
		_Head_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 6, 128 * 1, 128, 128));
		_Head_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 7, 128 * 1, 128, 128));
		_Head_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 8, 128 * 1, 128, 128));
		_Head_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 9, 128 * 1, 128, 128));
		_Head_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 10, 128 * 1, 128, 128));
		_Head_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 11, 128 * 1, 128, 128));
		_Head_Running_AnimationUp_Right.setSpriteSheet(*_textureHead);
		_Head_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 4, 128 * 3, 128, 128)); //Done
		_Head_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 5, 128 * 3, 128, 128));
		_Head_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 6, 128 * 3, 128, 128));
		_Head_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 7, 128 * 3, 128, 128));
		_Head_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 8, 128 * 3, 128, 128));
		_Head_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 9, 128 * 3, 128, 128));
		_Head_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 10, 128 * 3, 128, 128));
		_Head_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 11, 128 * 3, 128, 128));
		_Head_Running_AnimationDown_Left.setSpriteSheet(*_textureHead);
		_Head_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 4, 128 * 7, 128, 128)); //Done
		_Head_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 5, 128 * 7, 128, 128));
		_Head_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 6, 128 * 7, 128, 128));
		_Head_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 7, 128 * 7, 128, 128));
		_Head_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 8, 128 * 7, 128, 128));
		_Head_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 9, 128 * 7, 128, 128));
		_Head_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 10, 128 * 7, 128, 128));
		_Head_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 11, 128 * 7, 128, 128));
		_Head_Running_AnimationDown_Right.setSpriteSheet(*_textureHead);
		_Head_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 4, 128 * 5, 128, 128)); //Done
		_Head_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 5, 128 * 5, 128, 128));
		_Head_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 6, 128 * 5, 128, 128));
		_Head_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 7, 128 * 5, 128, 128));
		_Head_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 8, 128 * 5, 128, 128));
		_Head_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 9, 128 * 5, 128, 128));
		_Head_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 10, 128 * 5, 128, 128));
		_Head_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 11, 128 * 5, 128, 128));
	}

	// Melee Swing (4 frames)
	{
		_Head_MeleeSwing_AnimationUp.setSpriteSheet(*_textureHead);
		_Head_MeleeSwing_AnimationUp.addFrame(sf::IntRect(128 * 12, 128 * 2, 128, 128));
		_Head_MeleeSwing_AnimationUp.addFrame(sf::IntRect(128 * 13, 128 * 2, 128, 128));
		_Head_MeleeSwing_AnimationUp.addFrame(sf::IntRect(128 * 14, 128 * 2, 128, 128));
		_Head_MeleeSwing_AnimationUp.addFrame(sf::IntRect(128 * 15, 128 * 2, 128, 128));
		_Head_MeleeSwing_AnimationDown.setSpriteSheet(*_textureHead);
		_Head_MeleeSwing_AnimationDown.addFrame(sf::IntRect(128 * 12, 128 * 6, 128, 128));
		_Head_MeleeSwing_AnimationDown.addFrame(sf::IntRect(128 * 13, 128 * 6, 128, 128));
		_Head_MeleeSwing_AnimationDown.addFrame(sf::IntRect(128 * 14, 128 * 6, 128, 128));
		_Head_MeleeSwing_AnimationDown.addFrame(sf::IntRect(128 * 15, 128 * 6, 128, 128));
		_Head_MeleeSwing_AnimationLeft.setSpriteSheet(*_textureHead);
		_Head_MeleeSwing_AnimationLeft.addFrame(sf::IntRect(128 * 12, 128 * 0, 128, 128));
		_Head_MeleeSwing_AnimationLeft.addFrame(sf::IntRect(128 * 13, 128 * 0, 128, 128));
		_Head_MeleeSwing_AnimationLeft.addFrame(sf::IntRect(128 * 14, 128 * 0, 128, 128));
		_Head_MeleeSwing_AnimationLeft.addFrame(sf::IntRect(128 * 15, 128 * 0, 128, 128));
		_Head_MeleeSwing_AnimationRight.setSpriteSheet(*_textureHead);
		_Head_MeleeSwing_AnimationRight.addFrame(sf::IntRect(128 * 12, 128 * 4, 128, 128));
		_Head_MeleeSwing_AnimationRight.addFrame(sf::IntRect(128 * 13, 128 * 4, 128, 128));
		_Head_MeleeSwing_AnimationRight.addFrame(sf::IntRect(128 * 14, 128 * 4, 128, 128));
		_Head_MeleeSwing_AnimationRight.addFrame(sf::IntRect(128 * 15, 128 * 4, 128, 128));
		_Head_MeleeSwing_AnimationUp_Left.setSpriteSheet(*_textureHead);
		_Head_MeleeSwing_AnimationUp_Left.addFrame(sf::IntRect(128 * 12, 128 * 1, 128, 128));
		_Head_MeleeSwing_AnimationUp_Left.addFrame(sf::IntRect(128 * 13, 128 * 1, 128, 128));
		_Head_MeleeSwing_AnimationUp_Left.addFrame(sf::IntRect(128 * 14, 128 * 1, 128, 128));
		_Head_MeleeSwing_AnimationUp_Left.addFrame(sf::IntRect(128 * 15, 128 * 1, 128, 128));
		_Head_MeleeSwing_AnimationUp_Right.setSpriteSheet(*_textureHead);
		_Head_MeleeSwing_AnimationUp_Right.addFrame(sf::IntRect(128 * 12, 128 * 3, 128, 128));
		_Head_MeleeSwing_AnimationUp_Right.addFrame(sf::IntRect(128 * 13, 128 * 3, 128, 128));
		_Head_MeleeSwing_AnimationUp_Right.addFrame(sf::IntRect(128 * 14, 128 * 3, 128, 128));
		_Head_MeleeSwing_AnimationUp_Right.addFrame(sf::IntRect(128 * 15, 128 * 3, 128, 128));
		_Head_MeleeSwing_AnimationDown_Left.setSpriteSheet(*_textureHead);
		_Head_MeleeSwing_AnimationDown_Left.addFrame(sf::IntRect(128 * 12, 128 * 7, 128, 128));
		_Head_MeleeSwing_AnimationDown_Left.addFrame(sf::IntRect(128 * 13, 128 * 7, 128, 128));
		_Head_MeleeSwing_AnimationDown_Left.addFrame(sf::IntRect(128 * 14, 128 * 7, 128, 128));
		_Head_MeleeSwing_AnimationDown_Left.addFrame(sf::IntRect(128 * 15, 128 * 7, 128, 128));
		_Head_MeleeSwing_AnimationDown_Right.setSpriteSheet(*_textureHead);
		_Head_MeleeSwing_AnimationDown_Right.addFrame(sf::IntRect(128 * 12, 128 * 5, 128, 128));
		_Head_MeleeSwing_AnimationDown_Right.addFrame(sf::IntRect(128 * 13, 128 * 5, 128, 128));
		_Head_MeleeSwing_AnimationDown_Right.addFrame(sf::IntRect(128 * 14, 128 * 5, 128, 128));
		_Head_MeleeSwing_AnimationDown_Right.addFrame(sf::IntRect(128 * 15, 128 * 5, 128, 128));
	}

	// Block (2 frames)
	{
		_Head_Block_AnimationUp.setSpriteSheet(*_textureHead);
		_Head_Block_AnimationUp.addFrame(sf::IntRect(128 * 16, 128 * 2, 128, 128));
		_Head_Block_AnimationUp.addFrame(sf::IntRect(128 * 17, 128 * 2, 128, 128));
		_Head_Block_AnimationDown.setSpriteSheet(*_textureHead);
		_Head_Block_AnimationDown.addFrame(sf::IntRect(128 * 16, 128 * 6, 128, 128));
		_Head_Block_AnimationDown.addFrame(sf::IntRect(128 * 17, 128 * 6, 128, 128));
		_Head_Block_AnimationLeft.setSpriteSheet(*_textureHead);
		_Head_Block_AnimationLeft.addFrame(sf::IntRect(128 * 16, 128 * 0, 128, 128));
		_Head_Block_AnimationLeft.addFrame(sf::IntRect(128 * 17, 128 * 0, 128, 128));
		_Head_Block_AnimationRight.setSpriteSheet(*_textureHead);
		_Head_Block_AnimationRight.addFrame(sf::IntRect(128 * 16, 128 * 4, 128, 128));
		_Head_Block_AnimationRight.addFrame(sf::IntRect(128 * 17, 128 * 4, 128, 128));
		_Head_Block_AnimationUp_Left.setSpriteSheet(*_textureHead);
		_Head_Block_AnimationUp_Left.addFrame(sf::IntRect(128 * 16, 128 * 1, 128, 128));
		_Head_Block_AnimationUp_Left.addFrame(sf::IntRect(128 * 17, 128 * 1, 128, 128));
		_Head_Block_AnimationUp_Right.setSpriteSheet(*_textureHead);
		_Head_Block_AnimationUp_Right.addFrame(sf::IntRect(128 * 16, 128 * 3, 128, 128));
		_Head_Block_AnimationUp_Right.addFrame(sf::IntRect(128 * 17, 128 * 3, 128, 128));
		_Head_Block_AnimationDown_Left.setSpriteSheet(*_textureHead);
		_Head_Block_AnimationDown_Left.addFrame(sf::IntRect(128 * 16, 128 * 7, 128, 128));
		_Head_Block_AnimationDown_Left.addFrame(sf::IntRect(128 * 17, 128 * 7, 128, 128));
		_Head_Block_AnimationDown_Right.setSpriteSheet(*_textureHead);
		_Head_Block_AnimationDown_Right.addFrame(sf::IntRect(128 * 16, 128 * 5, 128, 128));
		_Head_Block_AnimationDown_Right.addFrame(sf::IntRect(128 * 17, 128 * 5, 128, 128));
	}

	// Hit and Die (6 frames)
	{
		_Head_HitDie_AnimationUp.setSpriteSheet(*_textureHead);
		_Head_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 18, 128 * 2, 128, 128)); //Done
		_Head_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 19, 128 * 2, 128, 128));
		_Head_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 20, 128 * 2, 128, 128));
		_Head_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 21, 128 * 2, 128, 128));
		_Head_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 22, 128 * 2, 128, 128));
		_Head_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 23, 128 * 2, 128, 128));
		_Head_HitDie_AnimationDown.setSpriteSheet(*_textureHead);
		_Head_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 18, 128 * 6, 128, 128)); //Done
		_Head_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 19, 128 * 6, 128, 128));
		_Head_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 20, 128 * 6, 128, 128));
		_Head_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 21, 128 * 6, 128, 128));
		_Head_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 22, 128 * 6, 128, 128));
		_Head_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 23, 128 * 6, 128, 128));
		_Head_HitDie_AnimationLeft.setSpriteSheet(*_textureHead);
		_Head_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 18, 128 * 0, 128, 128)); //Done
		_Head_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 19, 128 * 0, 128, 128));
		_Head_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 20, 128 * 0, 128, 128));
		_Head_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 21, 128 * 0, 128, 128));
		_Head_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 22, 128 * 0, 128, 128));
		_Head_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 23, 128 * 0, 128, 128));
		_Head_HitDie_AnimationRight.setSpriteSheet(*_textureHead);
		_Head_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 18, 128 * 4, 128, 128)); //Done
		_Head_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 19, 128 * 4, 128, 128));
		_Head_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 20, 128 * 4, 128, 128));
		_Head_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 21, 128 * 4, 128, 128));
		_Head_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 22, 128 * 4, 128, 128));
		_Head_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 23, 128 * 4, 128, 128));
		_Head_HitDie_AnimationUp_Left.setSpriteSheet(*_textureHead);
		_Head_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 18, 128 * 1, 128, 128)); //DONE
		_Head_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 19, 128 * 1, 128, 128));
		_Head_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 20, 128 * 1, 128, 128));
		_Head_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 21, 128 * 1, 128, 128));
		_Head_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 22, 128 * 1, 128, 128));
		_Head_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 23, 128 * 1, 128, 128));
		_Head_HitDie_AnimationUp_Right.setSpriteSheet(*_textureHead);
		_Head_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 18, 128 * 3, 128, 128)); //Done
		_Head_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 19, 128 * 3, 128, 128));
		_Head_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 20, 128 * 3, 128, 128));
		_Head_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 21, 128 * 3, 128, 128));
		_Head_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 22, 128 * 3, 128, 128));
		_Head_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 23, 128 * 3, 128, 128));
		_Head_HitDie_AnimationDown_Left.setSpriteSheet(*_textureHead);
		_Head_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 18, 128 * 7, 128, 128)); //Done
		_Head_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 19, 128 * 7, 128, 128));
		_Head_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 20, 128 * 7, 128, 128));
		_Head_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 21, 128 * 7, 128, 128));
		_Head_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 22, 128 * 7, 128, 128));
		_Head_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 23, 128 * 7, 128, 128));
		_Head_HitDie_AnimationDown_Right.setSpriteSheet(*_textureHead);
		_Head_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 18, 128 * 5, 128, 128)); //Done
		_Head_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 19, 128 * 5, 128, 128));
		_Head_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 20, 128 * 5, 128, 128));
		_Head_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 21, 128 * 5, 128, 128));
		_Head_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 22, 128 * 5, 128, 128));
		_Head_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 23, 128 * 5, 128, 128));
	}

	// Cast Spell (4 frames)
	{
		_Head_CastSpell_AnimationUp.setSpriteSheet(*_textureHead);
		_Head_CastSpell_AnimationUp.addFrame(sf::IntRect(128 * 24, 128 * 2, 128, 128));
		_Head_CastSpell_AnimationUp.addFrame(sf::IntRect(128 * 25, 128 * 2, 128, 128));
		_Head_CastSpell_AnimationUp.addFrame(sf::IntRect(128 * 26, 128 * 2, 128, 128));
		_Head_CastSpell_AnimationUp.addFrame(sf::IntRect(128 * 27, 128 * 2, 128, 128));
		_Head_CastSpell_AnimationDown.setSpriteSheet(*_textureHead);
		_Head_CastSpell_AnimationDown.addFrame(sf::IntRect(128 * 24, 128 * 6, 128, 128));
		_Head_CastSpell_AnimationDown.addFrame(sf::IntRect(128 * 25, 128 * 6, 128, 128));
		_Head_CastSpell_AnimationDown.addFrame(sf::IntRect(128 * 26, 128 * 6, 128, 128));
		_Head_CastSpell_AnimationDown.addFrame(sf::IntRect(128 * 27, 128 * 6, 128, 128));
		_Head_CastSpell_AnimationLeft.setSpriteSheet(*_textureHead);
		_Head_CastSpell_AnimationLeft.addFrame(sf::IntRect(128 * 24, 128 * 0, 128, 128));
		_Head_CastSpell_AnimationLeft.addFrame(sf::IntRect(128 * 25, 128 * 0, 128, 128));
		_Head_CastSpell_AnimationLeft.addFrame(sf::IntRect(128 * 26, 128 * 0, 128, 128));
		_Head_CastSpell_AnimationLeft.addFrame(sf::IntRect(128 * 27, 128 * 0, 128, 128));
		_Head_CastSpell_AnimationRight.setSpriteSheet(*_textureHead);
		_Head_CastSpell_AnimationRight.addFrame(sf::IntRect(128 * 24, 128 * 4, 128, 128));
		_Head_CastSpell_AnimationRight.addFrame(sf::IntRect(128 * 25, 128 * 4, 128, 128));
		_Head_CastSpell_AnimationRight.addFrame(sf::IntRect(128 * 26, 128 * 4, 128, 128));
		_Head_CastSpell_AnimationRight.addFrame(sf::IntRect(128 * 27, 128 * 4, 128, 128));
		_Head_CastSpell_AnimationUp_Left.setSpriteSheet(*_textureHead);
		_Head_CastSpell_AnimationUp_Left.addFrame(sf::IntRect(128 * 24, 128 * 1, 128, 128));
		_Head_CastSpell_AnimationUp_Left.addFrame(sf::IntRect(128 * 25, 128 * 1, 128, 128));
		_Head_CastSpell_AnimationUp_Left.addFrame(sf::IntRect(128 * 26, 128 * 1, 128, 128));
		_Head_CastSpell_AnimationUp_Left.addFrame(sf::IntRect(128 * 27, 128 * 1, 128, 128));
		_Head_CastSpell_AnimationUp_Right.setSpriteSheet(*_textureHead);
		_Head_CastSpell_AnimationUp_Right.addFrame(sf::IntRect(128 * 24, 128 * 3, 128, 128));
		_Head_CastSpell_AnimationUp_Right.addFrame(sf::IntRect(128 * 25, 128 * 3, 128, 128));
		_Head_CastSpell_AnimationUp_Right.addFrame(sf::IntRect(128 * 26, 128 * 3, 128, 128));
		_Head_CastSpell_AnimationUp_Right.addFrame(sf::IntRect(128 * 27, 128 * 3, 128, 128));
		_Head_CastSpell_AnimationDown_Left.setSpriteSheet(*_textureHead);
		_Head_CastSpell_AnimationDown_Left.addFrame(sf::IntRect(128 * 24, 128 * 7, 128, 128));
		_Head_CastSpell_AnimationDown_Left.addFrame(sf::IntRect(128 * 25, 128 * 7, 128, 128));
		_Head_CastSpell_AnimationDown_Left.addFrame(sf::IntRect(128 * 26, 128 * 7, 128, 128));
		_Head_CastSpell_AnimationDown_Left.addFrame(sf::IntRect(128 * 27, 128 * 7, 128, 128));
		_Head_CastSpell_AnimationDown_Right.setSpriteSheet(*_textureHead);
		_Head_CastSpell_AnimationDown_Right.addFrame(sf::IntRect(128 * 24, 128 * 5, 128, 128));
		_Head_CastSpell_AnimationDown_Right.addFrame(sf::IntRect(128 * 25, 128 * 5, 128, 128));
		_Head_CastSpell_AnimationDown_Right.addFrame(sf::IntRect(128 * 26, 128 * 5, 128, 128));
		_Head_CastSpell_AnimationDown_Right.addFrame(sf::IntRect(128 * 27, 128 * 5, 128, 128));
	}

	// Shoot Bow (4 frames)
	{
		_Head_ShootBow_AnimationUp.setSpriteSheet(*_textureHead);
		_Head_ShootBow_AnimationUp.addFrame(sf::IntRect(128 * 28, 128 * 2, 128, 128));
		_Head_ShootBow_AnimationUp.addFrame(sf::IntRect(128 * 29, 128 * 2, 128, 128));
		_Head_ShootBow_AnimationUp.addFrame(sf::IntRect(128 * 30, 128 * 2, 128, 128));
		_Head_ShootBow_AnimationUp.addFrame(sf::IntRect(128 * 31, 128 * 2, 128, 128));
		_Head_ShootBow_AnimationDown.setSpriteSheet(*_textureHead);
		_Head_ShootBow_AnimationDown.addFrame(sf::IntRect(128 * 28, 128 * 6, 128, 128));
		_Head_ShootBow_AnimationDown.addFrame(sf::IntRect(128 * 29, 128 * 6, 128, 128));
		_Head_ShootBow_AnimationDown.addFrame(sf::IntRect(128 * 30, 128 * 6, 128, 128));
		_Head_ShootBow_AnimationDown.addFrame(sf::IntRect(128 * 31, 128 * 6, 128, 128));
		_Head_ShootBow_AnimationLeft.setSpriteSheet(*_textureHead);
		_Head_ShootBow_AnimationLeft.addFrame(sf::IntRect(128 * 28, 128 * 0, 128, 128));
		_Head_ShootBow_AnimationLeft.addFrame(sf::IntRect(128 * 29, 128 * 0, 128, 128));
		_Head_ShootBow_AnimationLeft.addFrame(sf::IntRect(128 * 30, 128 * 0, 128, 128));
		_Head_ShootBow_AnimationLeft.addFrame(sf::IntRect(128 * 31, 128 * 0, 128, 128));
		_Head_ShootBow_AnimationRight.setSpriteSheet(*_textureHead);
		_Head_ShootBow_AnimationRight.addFrame(sf::IntRect(128 * 28, 128 * 4, 128, 128));
		_Head_ShootBow_AnimationRight.addFrame(sf::IntRect(128 * 29, 128 * 4, 128, 128));
		_Head_ShootBow_AnimationRight.addFrame(sf::IntRect(128 * 30, 128 * 4, 128, 128));
		_Head_ShootBow_AnimationRight.addFrame(sf::IntRect(128 * 31, 128 * 4, 128, 128));
		_Head_ShootBow_AnimationUp_Left.setSpriteSheet(*_textureHead);
		_Head_ShootBow_AnimationUp_Left.addFrame(sf::IntRect(128 * 28, 128 * 1, 128, 128));
		_Head_ShootBow_AnimationUp_Left.addFrame(sf::IntRect(128 * 29, 128 * 1, 128, 128));
		_Head_ShootBow_AnimationUp_Left.addFrame(sf::IntRect(128 * 30, 128 * 1, 128, 128));
		_Head_ShootBow_AnimationUp_Left.addFrame(sf::IntRect(128 * 31, 128 * 1, 128, 128));
		_Head_ShootBow_AnimationUp_Right.setSpriteSheet(*_textureHead);
		_Head_ShootBow_AnimationUp_Right.addFrame(sf::IntRect(128 * 28, 128 * 3, 128, 128));
		_Head_ShootBow_AnimationUp_Right.addFrame(sf::IntRect(128 * 29, 128 * 3, 128, 128));
		_Head_ShootBow_AnimationUp_Right.addFrame(sf::IntRect(128 * 30, 128 * 3, 128, 128));
		_Head_ShootBow_AnimationUp_Right.addFrame(sf::IntRect(128 * 31, 128 * 3, 128, 128));
		_Head_ShootBow_AnimationDown_Left.setSpriteSheet(*_textureHead);
		_Head_ShootBow_AnimationDown_Left.addFrame(sf::IntRect(128 * 28, 128 * 7, 128, 128));
		_Head_ShootBow_AnimationDown_Left.addFrame(sf::IntRect(128 * 29, 128 * 7, 128, 128));
		_Head_ShootBow_AnimationDown_Left.addFrame(sf::IntRect(128 * 30, 128 * 7, 128, 128));
		_Head_ShootBow_AnimationDown_Left.addFrame(sf::IntRect(128 * 31, 128 * 7, 128, 128));
		_Head_ShootBow_AnimationDown_Right.setSpriteSheet(*_textureHead);
		_Head_ShootBow_AnimationDown_Right.addFrame(sf::IntRect(128 * 28, 128 * 5, 128, 128));
		_Head_ShootBow_AnimationDown_Right.addFrame(sf::IntRect(128 * 29, 128 * 5, 128, 128));
		_Head_ShootBow_AnimationDown_Right.addFrame(sf::IntRect(128 * 30, 128 * 5, 128, 128));
		_Head_ShootBow_AnimationDown_Right.addFrame(sf::IntRect(128 * 31, 128 * 5, 128, 128));
	}
}

void Player::initWeaponTextures()
{
	// Stance (4 frames)
	{
		_Weapon_Stance_AnimationUp.setSpriteSheet(*_textureWeapon);
		_Weapon_Stance_AnimationUp.addFrame(sf::IntRect(128 * 0, 128 * 2, 128, 128));
		_Weapon_Stance_AnimationUp.addFrame(sf::IntRect(128 * 1, 128 * 2, 128, 128));
		_Weapon_Stance_AnimationUp.addFrame(sf::IntRect(128 * 2, 128 * 2, 128, 128));
		_Weapon_Stance_AnimationUp.addFrame(sf::IntRect(128 * 3, 128 * 2, 128, 128));
		_Weapon_Stance_AnimationDown.setSpriteSheet(*_textureWeapon);
		_Weapon_Stance_AnimationDown.addFrame(sf::IntRect(128 * 0, 128 * 6, 128, 128));
		_Weapon_Stance_AnimationDown.addFrame(sf::IntRect(128 * 1, 128 * 6, 128, 128));
		_Weapon_Stance_AnimationDown.addFrame(sf::IntRect(128 * 2, 128 * 6, 128, 128));
		_Weapon_Stance_AnimationDown.addFrame(sf::IntRect(128 * 3, 128 * 6, 128, 128));
		_Weapon_Stance_AnimationLeft.setSpriteSheet(*_textureWeapon);
		_Weapon_Stance_AnimationLeft.addFrame(sf::IntRect(128 * 0, 128 * 0, 128, 128));
		_Weapon_Stance_AnimationLeft.addFrame(sf::IntRect(128 * 1, 128 * 0, 128, 128));
		_Weapon_Stance_AnimationLeft.addFrame(sf::IntRect(128 * 2, 128 * 0, 128, 128));
		_Weapon_Stance_AnimationLeft.addFrame(sf::IntRect(128 * 3, 128 * 0, 128, 128));
		_Weapon_Stance_AnimationRight.setSpriteSheet(*_textureWeapon);
		_Weapon_Stance_AnimationRight.addFrame(sf::IntRect(128 * 0, 128 * 4, 128, 128));
		_Weapon_Stance_AnimationRight.addFrame(sf::IntRect(128 * 1, 128 * 4, 128, 128));
		_Weapon_Stance_AnimationRight.addFrame(sf::IntRect(128 * 2, 128 * 4, 128, 128));
		_Weapon_Stance_AnimationRight.addFrame(sf::IntRect(128 * 3, 128 * 4, 128, 128));
		_Weapon_Stance_AnimationUp_Left.setSpriteSheet(*_textureWeapon);
		_Weapon_Stance_AnimationUp_Left.addFrame(sf::IntRect(128 * 0, 128 * 0, 128, 128));
		_Weapon_Stance_AnimationUp_Left.addFrame(sf::IntRect(128 * 1, 128 * 0, 128, 128));
		_Weapon_Stance_AnimationUp_Left.addFrame(sf::IntRect(128 * 2, 128 * 0, 128, 128));
		_Weapon_Stance_AnimationUp_Left.addFrame(sf::IntRect(128 * 3, 128 * 0, 128, 128));
		_Weapon_Stance_AnimationUp_Right.setSpriteSheet(*_textureWeapon);
		_Weapon_Stance_AnimationUp_Right.addFrame(sf::IntRect(128 * 0, 128 * 3, 128, 128));
		_Weapon_Stance_AnimationUp_Right.addFrame(sf::IntRect(128 * 1, 128 * 3, 128, 128));
		_Weapon_Stance_AnimationUp_Right.addFrame(sf::IntRect(128 * 2, 128 * 3, 128, 128));
		_Weapon_Stance_AnimationUp_Right.addFrame(sf::IntRect(128 * 3, 128 * 3, 128, 128));
		_Weapon_Stance_AnimationDown_Left.setSpriteSheet(*_textureWeapon);
		_Weapon_Stance_AnimationDown_Left.addFrame(sf::IntRect(128 * 0, 128 * 7, 128, 128));
		_Weapon_Stance_AnimationDown_Left.addFrame(sf::IntRect(128 * 1, 128 * 7, 128, 128));
		_Weapon_Stance_AnimationDown_Left.addFrame(sf::IntRect(128 * 2, 128 * 7, 128, 128));
		_Weapon_Stance_AnimationDown_Left.addFrame(sf::IntRect(128 * 3, 128 * 7, 128, 128));
		_Weapon_Stance_AnimationDown_Right.setSpriteSheet(*_textureWeapon);
		_Weapon_Stance_AnimationDown_Right.addFrame(sf::IntRect(128 * 0, 128 * 5, 128, 128));
		_Weapon_Stance_AnimationDown_Right.addFrame(sf::IntRect(128 * 1, 128 * 5, 128, 128));
		_Weapon_Stance_AnimationDown_Right.addFrame(sf::IntRect(128 * 2, 128 * 5, 128, 128));
		_Weapon_Stance_AnimationDown_Right.addFrame(sf::IntRect(128 * 3, 128 * 5, 128, 128));
	}

	// Running (8 frames)
	{
		_Weapon_Running_AnimationUp.setSpriteSheet(*_textureWeapon);
		_Weapon_Running_AnimationUp.addFrame(sf::IntRect(128 * 4, 128 * 2, 128, 128)); //Done
		_Weapon_Running_AnimationUp.addFrame(sf::IntRect(128 * 5, 128 * 2, 128, 128));
		_Weapon_Running_AnimationUp.addFrame(sf::IntRect(128 * 6, 128 * 2, 128, 128));
		_Weapon_Running_AnimationUp.addFrame(sf::IntRect(128 * 7, 128 * 2, 128, 128));
		_Weapon_Running_AnimationUp.addFrame(sf::IntRect(128 * 8, 128 * 2, 128, 128));
		_Weapon_Running_AnimationUp.addFrame(sf::IntRect(128 * 9, 128 * 2, 128, 128));
		_Weapon_Running_AnimationUp.addFrame(sf::IntRect(128 * 10, 128 * 2, 128, 128));
		_Weapon_Running_AnimationUp.addFrame(sf::IntRect(128 * 11, 128 * 2, 128, 128));
		_Weapon_Running_AnimationDown.setSpriteSheet(*_textureWeapon);
		_Weapon_Running_AnimationDown.addFrame(sf::IntRect(128 * 4, 128 * 6, 128, 128)); //Done
		_Weapon_Running_AnimationDown.addFrame(sf::IntRect(128 * 5, 128 * 6, 128, 128));
		_Weapon_Running_AnimationDown.addFrame(sf::IntRect(128 * 6, 128 * 6, 128, 128));
		_Weapon_Running_AnimationDown.addFrame(sf::IntRect(128 * 7, 128 * 6, 128, 128));
		_Weapon_Running_AnimationDown.addFrame(sf::IntRect(128 * 8, 128 * 6, 128, 128));
		_Weapon_Running_AnimationDown.addFrame(sf::IntRect(128 * 9, 128 * 6, 128, 128));
		_Weapon_Running_AnimationDown.addFrame(sf::IntRect(128 * 10, 128 * 6, 128, 128));
		_Weapon_Running_AnimationDown.addFrame(sf::IntRect(128 * 11, 128 * 6, 128, 128));
		_Weapon_Running_AnimationLeft.setSpriteSheet(*_textureWeapon);
		_Weapon_Running_AnimationLeft.addFrame(sf::IntRect(128 * 4, 128 * 0, 128, 128)); //Done
		_Weapon_Running_AnimationLeft.addFrame(sf::IntRect(128 * 5, 128 * 0, 128, 128));
		_Weapon_Running_AnimationLeft.addFrame(sf::IntRect(128 * 6, 128 * 0, 128, 128));
		_Weapon_Running_AnimationLeft.addFrame(sf::IntRect(128 * 7, 128 * 0, 128, 128));
		_Weapon_Running_AnimationLeft.addFrame(sf::IntRect(128 * 8, 128 * 0, 128, 128));
		_Weapon_Running_AnimationLeft.addFrame(sf::IntRect(128 * 9, 128 * 0, 128, 128));
		_Weapon_Running_AnimationLeft.addFrame(sf::IntRect(128 * 10, 128 * 0, 128, 128));
		_Weapon_Running_AnimationLeft.addFrame(sf::IntRect(128 * 11, 128 * 0, 128, 128));
		_Weapon_Running_AnimationRight.setSpriteSheet(*_textureWeapon);
		_Weapon_Running_AnimationRight.addFrame(sf::IntRect(128 * 4, 128 * 4, 128, 128)); //Done
		_Weapon_Running_AnimationRight.addFrame(sf::IntRect(128 * 5, 128 * 4, 128, 128));
		_Weapon_Running_AnimationRight.addFrame(sf::IntRect(128 * 6, 128 * 4, 128, 128));
		_Weapon_Running_AnimationRight.addFrame(sf::IntRect(128 * 7, 128 * 4, 128, 128));
		_Weapon_Running_AnimationRight.addFrame(sf::IntRect(128 * 8, 128 * 4, 128, 128));
		_Weapon_Running_AnimationRight.addFrame(sf::IntRect(128 * 9, 128 * 4, 128, 128));
		_Weapon_Running_AnimationRight.addFrame(sf::IntRect(128 * 10, 128 * 4, 128, 128));
		_Weapon_Running_AnimationRight.addFrame(sf::IntRect(128 * 11, 128 * 4, 128, 128));
		_Weapon_Running_AnimationUp_Left.setSpriteSheet(*_textureWeapon);
		_Weapon_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 4, 128 * 1, 128, 128)); //DONE
		_Weapon_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 5, 128 * 1, 128, 128));
		_Weapon_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 6, 128 * 1, 128, 128));
		_Weapon_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 7, 128 * 1, 128, 128));
		_Weapon_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 8, 128 * 1, 128, 128));
		_Weapon_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 9, 128 * 1, 128, 128));
		_Weapon_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 10, 128 * 1, 128, 128));
		_Weapon_Running_AnimationUp_Left.addFrame(sf::IntRect(128 * 11, 128 * 1, 128, 128));
		_Weapon_Running_AnimationUp_Right.setSpriteSheet(*_textureWeapon);
		_Weapon_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 4, 128 * 3, 128, 128)); //Done
		_Weapon_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 5, 128 * 3, 128, 128));
		_Weapon_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 6, 128 * 3, 128, 128));
		_Weapon_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 7, 128 * 3, 128, 128));
		_Weapon_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 8, 128 * 3, 128, 128));
		_Weapon_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 9, 128 * 3, 128, 128));
		_Weapon_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 10, 128 * 3, 128, 128));
		_Weapon_Running_AnimationUp_Right.addFrame(sf::IntRect(128 * 11, 128 * 3, 128, 128));
		_Weapon_Running_AnimationDown_Left.setSpriteSheet(*_textureWeapon);
		_Weapon_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 4, 128 * 7, 128, 128)); //Done
		_Weapon_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 5, 128 * 7, 128, 128));
		_Weapon_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 6, 128 * 7, 128, 128));
		_Weapon_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 7, 128 * 7, 128, 128));
		_Weapon_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 8, 128 * 7, 128, 128));
		_Weapon_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 9, 128 * 7, 128, 128));
		_Weapon_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 10, 128 * 7, 128, 128));
		_Weapon_Running_AnimationDown_Left.addFrame(sf::IntRect(128 * 11, 128 * 7, 128, 128));
		_Weapon_Running_AnimationDown_Right.setSpriteSheet(*_textureWeapon);
		_Weapon_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 4, 128 * 5, 128, 128)); //Done
		_Weapon_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 5, 128 * 5, 128, 128));
		_Weapon_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 6, 128 * 5, 128, 128));
		_Weapon_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 7, 128 * 5, 128, 128));
		_Weapon_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 8, 128 * 5, 128, 128));
		_Weapon_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 9, 128 * 5, 128, 128));
		_Weapon_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 10, 128 * 5, 128, 128));
		_Weapon_Running_AnimationDown_Right.addFrame(sf::IntRect(128 * 11, 128 * 5, 128, 128));
	}

	// Melee Swing (4 frames)
	{
		_Weapon_MeleeSwing_AnimationUp.setSpriteSheet(*_textureWeapon);
		_Weapon_MeleeSwing_AnimationUp.addFrame(sf::IntRect(128 * 12, 128 * 2, 128, 128));
		_Weapon_MeleeSwing_AnimationUp.addFrame(sf::IntRect(128 * 13, 128 * 2, 128, 128));
		_Weapon_MeleeSwing_AnimationUp.addFrame(sf::IntRect(128 * 14, 128 * 2, 128, 128));
		_Weapon_MeleeSwing_AnimationUp.addFrame(sf::IntRect(128 * 15, 128 * 2, 128, 128));
		_Weapon_MeleeSwing_AnimationDown.setSpriteSheet(*_textureWeapon);
		_Weapon_MeleeSwing_AnimationDown.addFrame(sf::IntRect(128 * 12, 128 * 6, 128, 128));
		_Weapon_MeleeSwing_AnimationDown.addFrame(sf::IntRect(128 * 13, 128 * 6, 128, 128));
		_Weapon_MeleeSwing_AnimationDown.addFrame(sf::IntRect(128 * 14, 128 * 6, 128, 128));
		_Weapon_MeleeSwing_AnimationDown.addFrame(sf::IntRect(128 * 15, 128 * 6, 128, 128));
		_Weapon_MeleeSwing_AnimationLeft.setSpriteSheet(*_textureWeapon);
		_Weapon_MeleeSwing_AnimationLeft.addFrame(sf::IntRect(128 * 12, 128 * 0, 128, 128));
		_Weapon_MeleeSwing_AnimationLeft.addFrame(sf::IntRect(128 * 13, 128 * 0, 128, 128));
		_Weapon_MeleeSwing_AnimationLeft.addFrame(sf::IntRect(128 * 14, 128 * 0, 128, 128));
		_Weapon_MeleeSwing_AnimationLeft.addFrame(sf::IntRect(128 * 15, 128 * 0, 128, 128));
		_Weapon_MeleeSwing_AnimationRight.setSpriteSheet(*_textureWeapon);
		_Weapon_MeleeSwing_AnimationRight.addFrame(sf::IntRect(128 * 12, 128 * 4, 128, 128));
		_Weapon_MeleeSwing_AnimationRight.addFrame(sf::IntRect(128 * 13, 128 * 4, 128, 128));
		_Weapon_MeleeSwing_AnimationRight.addFrame(sf::IntRect(128 * 14, 128 * 4, 128, 128));
		_Weapon_MeleeSwing_AnimationRight.addFrame(sf::IntRect(128 * 15, 128 * 4, 128, 128));
		_Weapon_MeleeSwing_AnimationUp_Left.setSpriteSheet(*_textureWeapon);
		_Weapon_MeleeSwing_AnimationUp_Left.addFrame(sf::IntRect(128 * 12, 128 * 1, 128, 128));
		_Weapon_MeleeSwing_AnimationUp_Left.addFrame(sf::IntRect(128 * 13, 128 * 1, 128, 128));
		_Weapon_MeleeSwing_AnimationUp_Left.addFrame(sf::IntRect(128 * 14, 128 * 1, 128, 128));
		_Weapon_MeleeSwing_AnimationUp_Left.addFrame(sf::IntRect(128 * 15, 128 * 1, 128, 128));
		_Weapon_MeleeSwing_AnimationUp_Right.setSpriteSheet(*_textureWeapon);
		_Weapon_MeleeSwing_AnimationUp_Right.addFrame(sf::IntRect(128 * 12, 128 * 3, 128, 128));
		_Weapon_MeleeSwing_AnimationUp_Right.addFrame(sf::IntRect(128 * 13, 128 * 3, 128, 128));
		_Weapon_MeleeSwing_AnimationUp_Right.addFrame(sf::IntRect(128 * 14, 128 * 3, 128, 128));
		_Weapon_MeleeSwing_AnimationUp_Right.addFrame(sf::IntRect(128 * 15, 128 * 3, 128, 128));
		_Weapon_MeleeSwing_AnimationDown_Left.setSpriteSheet(*_textureWeapon);
		_Weapon_MeleeSwing_AnimationDown_Left.addFrame(sf::IntRect(128 * 12, 128 * 7, 128, 128));
		_Weapon_MeleeSwing_AnimationDown_Left.addFrame(sf::IntRect(128 * 13, 128 * 7, 128, 128));
		_Weapon_MeleeSwing_AnimationDown_Left.addFrame(sf::IntRect(128 * 14, 128 * 7, 128, 128));
		_Weapon_MeleeSwing_AnimationDown_Left.addFrame(sf::IntRect(128 * 15, 128 * 7, 128, 128));
		_Weapon_MeleeSwing_AnimationDown_Right.setSpriteSheet(*_textureWeapon);
		_Weapon_MeleeSwing_AnimationDown_Right.addFrame(sf::IntRect(128 * 12, 128 * 5, 128, 128));
		_Weapon_MeleeSwing_AnimationDown_Right.addFrame(sf::IntRect(128 * 13, 128 * 5, 128, 128));
		_Weapon_MeleeSwing_AnimationDown_Right.addFrame(sf::IntRect(128 * 14, 128 * 5, 128, 128));
		_Weapon_MeleeSwing_AnimationDown_Right.addFrame(sf::IntRect(128 * 15, 128 * 5, 128, 128));
	}

	// Block (2 frames)
	{
		_Weapon_Block_AnimationUp.setSpriteSheet(*_textureWeapon);
		_Weapon_Block_AnimationUp.addFrame(sf::IntRect(128 * 16, 128 * 2, 128, 128));
		_Weapon_Block_AnimationUp.addFrame(sf::IntRect(128 * 17, 128 * 2, 128, 128));
		_Weapon_Block_AnimationDown.setSpriteSheet(*_textureWeapon);
		_Weapon_Block_AnimationDown.addFrame(sf::IntRect(128 * 16, 128 * 6, 128, 128));
		_Weapon_Block_AnimationDown.addFrame(sf::IntRect(128 * 17, 128 * 6, 128, 128));
		_Weapon_Block_AnimationLeft.setSpriteSheet(*_textureWeapon);
		_Weapon_Block_AnimationLeft.addFrame(sf::IntRect(128 * 16, 128 * 0, 128, 128));
		_Weapon_Block_AnimationLeft.addFrame(sf::IntRect(128 * 17, 128 * 0, 128, 128));
		_Weapon_Block_AnimationRight.setSpriteSheet(*_textureWeapon);
		_Weapon_Block_AnimationRight.addFrame(sf::IntRect(128 * 16, 128 * 4, 128, 128));
		_Weapon_Block_AnimationRight.addFrame(sf::IntRect(128 * 17, 128 * 4, 128, 128));
		_Weapon_Block_AnimationUp_Left.setSpriteSheet(*_textureWeapon);
		_Weapon_Block_AnimationUp_Left.addFrame(sf::IntRect(128 * 16, 128 * 1, 128, 128));
		_Weapon_Block_AnimationUp_Left.addFrame(sf::IntRect(128 * 17, 128 * 1, 128, 128));
		_Weapon_Block_AnimationUp_Right.setSpriteSheet(*_textureWeapon);
		_Weapon_Block_AnimationUp_Right.addFrame(sf::IntRect(128 * 16, 128 * 3, 128, 128));
		_Weapon_Block_AnimationUp_Right.addFrame(sf::IntRect(128 * 17, 128 * 3, 128, 128));
		_Weapon_Block_AnimationDown_Left.setSpriteSheet(*_textureWeapon);
		_Weapon_Block_AnimationDown_Left.addFrame(sf::IntRect(128 * 16, 128 * 7, 128, 128));
		_Weapon_Block_AnimationDown_Left.addFrame(sf::IntRect(128 * 17, 128 * 7, 128, 128));
		_Weapon_Block_AnimationDown_Right.setSpriteSheet(*_textureWeapon);
		_Weapon_Block_AnimationDown_Right.addFrame(sf::IntRect(128 * 16, 128 * 5, 128, 128));
		_Weapon_Block_AnimationDown_Right.addFrame(sf::IntRect(128 * 17, 128 * 5, 128, 128));
	}

	// Hit and Die (6 frames)
	{
		_Weapon_HitDie_AnimationUp.setSpriteSheet(*_textureWeapon);
		_Weapon_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 18, 128 * 2, 128, 128)); //Done
		_Weapon_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 19, 128 * 2, 128, 128));
		_Weapon_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 20, 128 * 2, 128, 128));
		_Weapon_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 21, 128 * 2, 128, 128));
		_Weapon_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 22, 128 * 2, 128, 128));
		_Weapon_HitDie_AnimationUp.addFrame(sf::IntRect(128 * 23, 128 * 2, 128, 128));
		_Weapon_HitDie_AnimationDown.setSpriteSheet(*_textureWeapon);
		_Weapon_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 18, 128 * 6, 128, 128)); //Done
		_Weapon_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 19, 128 * 6, 128, 128));
		_Weapon_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 20, 128 * 6, 128, 128));
		_Weapon_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 21, 128 * 6, 128, 128));
		_Weapon_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 22, 128 * 6, 128, 128));
		_Weapon_HitDie_AnimationDown.addFrame(sf::IntRect(128 * 23, 128 * 6, 128, 128));
		_Weapon_HitDie_AnimationLeft.setSpriteSheet(*_textureWeapon);
		_Weapon_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 18, 128 * 0, 128, 128)); //Done
		_Weapon_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 19, 128 * 0, 128, 128));
		_Weapon_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 20, 128 * 0, 128, 128));
		_Weapon_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 21, 128 * 0, 128, 128));
		_Weapon_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 22, 128 * 0, 128, 128));
		_Weapon_HitDie_AnimationLeft.addFrame(sf::IntRect(128 * 23, 128 * 0, 128, 128));
		_Weapon_HitDie_AnimationRight.setSpriteSheet(*_textureWeapon);
		_Weapon_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 18, 128 * 4, 128, 128)); //Done
		_Weapon_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 19, 128 * 4, 128, 128));
		_Weapon_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 20, 128 * 4, 128, 128));
		_Weapon_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 21, 128 * 4, 128, 128));
		_Weapon_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 22, 128 * 4, 128, 128));
		_Weapon_HitDie_AnimationRight.addFrame(sf::IntRect(128 * 23, 128 * 4, 128, 128));
		_Weapon_HitDie_AnimationUp_Left.setSpriteSheet(*_textureWeapon);
		_Weapon_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 18, 128 * 1, 128, 128)); //DONE
		_Weapon_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 19, 128 * 1, 128, 128));
		_Weapon_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 20, 128 * 1, 128, 128));
		_Weapon_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 21, 128 * 1, 128, 128));
		_Weapon_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 22, 128 * 1, 128, 128));
		_Weapon_HitDie_AnimationUp_Left.addFrame(sf::IntRect(128 * 23, 128 * 1, 128, 128));
		_Weapon_HitDie_AnimationUp_Right.setSpriteSheet(*_textureWeapon);
		_Weapon_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 18, 128 * 3, 128, 128)); //Done
		_Weapon_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 19, 128 * 3, 128, 128));
		_Weapon_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 20, 128 * 3, 128, 128));
		_Weapon_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 21, 128 * 3, 128, 128));
		_Weapon_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 22, 128 * 3, 128, 128));
		_Weapon_HitDie_AnimationUp_Right.addFrame(sf::IntRect(128 * 23, 128 * 3, 128, 128));
		_Weapon_HitDie_AnimationDown_Left.setSpriteSheet(*_textureWeapon);
		_Weapon_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 18, 128 * 7, 128, 128)); //Done
		_Weapon_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 19, 128 * 7, 128, 128));
		_Weapon_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 20, 128 * 7, 128, 128));
		_Weapon_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 21, 128 * 7, 128, 128));
		_Weapon_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 22, 128 * 7, 128, 128));
		_Weapon_HitDie_AnimationDown_Left.addFrame(sf::IntRect(128 * 23, 128 * 7, 128, 128));
		_Weapon_HitDie_AnimationDown_Right.setSpriteSheet(*_textureWeapon);
		_Weapon_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 18, 128 * 5, 128, 128)); //Done
		_Weapon_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 19, 128 * 5, 128, 128));
		_Weapon_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 20, 128 * 5, 128, 128));
		_Weapon_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 21, 128 * 5, 128, 128));
		_Weapon_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 22, 128 * 5, 128, 128));
		_Weapon_HitDie_AnimationDown_Right.addFrame(sf::IntRect(128 * 23, 128 * 5, 128, 128));
	}

	// Cast Spell (4 frames)
	{
		_Weapon_CastSpell_AnimationUp.setSpriteSheet(*_textureWeapon);
		_Weapon_CastSpell_AnimationUp.addFrame(sf::IntRect(128 * 24, 128 * 2, 128, 128));
		_Weapon_CastSpell_AnimationUp.addFrame(sf::IntRect(128 * 25, 128 * 2, 128, 128));
		_Weapon_CastSpell_AnimationUp.addFrame(sf::IntRect(128 * 26, 128 * 2, 128, 128));
		_Weapon_CastSpell_AnimationUp.addFrame(sf::IntRect(128 * 27, 128 * 2, 128, 128));
		_Weapon_CastSpell_AnimationDown.setSpriteSheet(*_textureWeapon);
		_Weapon_CastSpell_AnimationDown.addFrame(sf::IntRect(128 * 24, 128 * 6, 128, 128));
		_Weapon_CastSpell_AnimationDown.addFrame(sf::IntRect(128 * 25, 128 * 6, 128, 128));
		_Weapon_CastSpell_AnimationDown.addFrame(sf::IntRect(128 * 26, 128 * 6, 128, 128));
		_Weapon_CastSpell_AnimationDown.addFrame(sf::IntRect(128 * 27, 128 * 6, 128, 128));
		_Weapon_CastSpell_AnimationLeft.setSpriteSheet(*_textureWeapon);
		_Weapon_CastSpell_AnimationLeft.addFrame(sf::IntRect(128 * 24, 128 * 0, 128, 128));
		_Weapon_CastSpell_AnimationLeft.addFrame(sf::IntRect(128 * 25, 128 * 0, 128, 128));
		_Weapon_CastSpell_AnimationLeft.addFrame(sf::IntRect(128 * 26, 128 * 0, 128, 128));
		_Weapon_CastSpell_AnimationLeft.addFrame(sf::IntRect(128 * 27, 128 * 0, 128, 128));
		_Weapon_CastSpell_AnimationRight.setSpriteSheet(*_textureWeapon);
		_Weapon_CastSpell_AnimationRight.addFrame(sf::IntRect(128 * 24, 128 * 4, 128, 128));
		_Weapon_CastSpell_AnimationRight.addFrame(sf::IntRect(128 * 25, 128 * 4, 128, 128));
		_Weapon_CastSpell_AnimationRight.addFrame(sf::IntRect(128 * 26, 128 * 4, 128, 128));
		_Weapon_CastSpell_AnimationRight.addFrame(sf::IntRect(128 * 27, 128 * 4, 128, 128));
		_Weapon_CastSpell_AnimationUp_Left.setSpriteSheet(*_textureWeapon);
		_Weapon_CastSpell_AnimationUp_Left.addFrame(sf::IntRect(128 * 24, 128 * 1, 128, 128));
		_Weapon_CastSpell_AnimationUp_Left.addFrame(sf::IntRect(128 * 25, 128 * 1, 128, 128));
		_Weapon_CastSpell_AnimationUp_Left.addFrame(sf::IntRect(128 * 26, 128 * 1, 128, 128));
		_Weapon_CastSpell_AnimationUp_Left.addFrame(sf::IntRect(128 * 27, 128 * 1, 128, 128));
		_Weapon_CastSpell_AnimationUp_Right.setSpriteSheet(*_textureWeapon);
		_Weapon_CastSpell_AnimationUp_Right.addFrame(sf::IntRect(128 * 24, 128 * 3, 128, 128));
		_Weapon_CastSpell_AnimationUp_Right.addFrame(sf::IntRect(128 * 25, 128 * 3, 128, 128));
		_Weapon_CastSpell_AnimationUp_Right.addFrame(sf::IntRect(128 * 26, 128 * 3, 128, 128));
		_Weapon_CastSpell_AnimationUp_Right.addFrame(sf::IntRect(128 * 27, 128 * 3, 128, 128));
		_Weapon_CastSpell_AnimationDown_Left.setSpriteSheet(*_textureWeapon);
		_Weapon_CastSpell_AnimationDown_Left.addFrame(sf::IntRect(128 * 24, 128 * 7, 128, 128));
		_Weapon_CastSpell_AnimationDown_Left.addFrame(sf::IntRect(128 * 25, 128 * 7, 128, 128));
		_Weapon_CastSpell_AnimationDown_Left.addFrame(sf::IntRect(128 * 26, 128 * 7, 128, 128));
		_Weapon_CastSpell_AnimationDown_Left.addFrame(sf::IntRect(128 * 27, 128 * 7, 128, 128));
		_Weapon_CastSpell_AnimationDown_Right.setSpriteSheet(*_textureWeapon);
		_Weapon_CastSpell_AnimationDown_Right.addFrame(sf::IntRect(128 * 24, 128 * 5, 128, 128));
		_Weapon_CastSpell_AnimationDown_Right.addFrame(sf::IntRect(128 * 25, 128 * 5, 128, 128));
		_Weapon_CastSpell_AnimationDown_Right.addFrame(sf::IntRect(128 * 26, 128 * 5, 128, 128));
		_Weapon_CastSpell_AnimationDown_Right.addFrame(sf::IntRect(128 * 27, 128 * 5, 128, 128));
	}

	// Shoot Bow (4 frames)
	{
		_Weapon_ShootBow_AnimationUp.setSpriteSheet(*_textureWeapon);
		_Weapon_ShootBow_AnimationUp.addFrame(sf::IntRect(128 * 28, 128 * 2, 128, 128));
		_Weapon_ShootBow_AnimationUp.addFrame(sf::IntRect(128 * 29, 128 * 2, 128, 128));
		_Weapon_ShootBow_AnimationUp.addFrame(sf::IntRect(128 * 30, 128 * 2, 128, 128));
		_Weapon_ShootBow_AnimationUp.addFrame(sf::IntRect(128 * 31, 128 * 2, 128, 128));
		_Weapon_ShootBow_AnimationDown.setSpriteSheet(*_textureWeapon);
		_Weapon_ShootBow_AnimationDown.addFrame(sf::IntRect(128 * 28, 128 * 6, 128, 128));
		_Weapon_ShootBow_AnimationDown.addFrame(sf::IntRect(128 * 29, 128 * 6, 128, 128));
		_Weapon_ShootBow_AnimationDown.addFrame(sf::IntRect(128 * 30, 128 * 6, 128, 128));
		_Weapon_ShootBow_AnimationDown.addFrame(sf::IntRect(128 * 31, 128 * 6, 128, 128));
		_Weapon_ShootBow_AnimationLeft.setSpriteSheet(*_textureWeapon);
		_Weapon_ShootBow_AnimationLeft.addFrame(sf::IntRect(128 * 28, 128 * 0, 128, 128));
		_Weapon_ShootBow_AnimationLeft.addFrame(sf::IntRect(128 * 29, 128 * 0, 128, 128));
		_Weapon_ShootBow_AnimationLeft.addFrame(sf::IntRect(128 * 30, 128 * 0, 128, 128));
		_Weapon_ShootBow_AnimationLeft.addFrame(sf::IntRect(128 * 31, 128 * 0, 128, 128));
		_Weapon_ShootBow_AnimationRight.setSpriteSheet(*_textureWeapon);
		_Weapon_ShootBow_AnimationRight.addFrame(sf::IntRect(128 * 28, 128 * 4, 128, 128));
		_Weapon_ShootBow_AnimationRight.addFrame(sf::IntRect(128 * 29, 128 * 4, 128, 128));
		_Weapon_ShootBow_AnimationRight.addFrame(sf::IntRect(128 * 30, 128 * 4, 128, 128));
		_Weapon_ShootBow_AnimationRight.addFrame(sf::IntRect(128 * 31, 128 * 4, 128, 128));
		_Weapon_ShootBow_AnimationUp_Left.setSpriteSheet(*_textureWeapon);
		_Weapon_ShootBow_AnimationUp_Left.addFrame(sf::IntRect(128 * 28, 128 * 1, 128, 128));
		_Weapon_ShootBow_AnimationUp_Left.addFrame(sf::IntRect(128 * 29, 128 * 1, 128, 128));
		_Weapon_ShootBow_AnimationUp_Left.addFrame(sf::IntRect(128 * 30, 128 * 1, 128, 128));
		_Weapon_ShootBow_AnimationUp_Left.addFrame(sf::IntRect(128 * 31, 128 * 1, 128, 128));
		_Weapon_ShootBow_AnimationUp_Right.setSpriteSheet(*_textureWeapon);
		_Weapon_ShootBow_AnimationUp_Right.addFrame(sf::IntRect(128 * 28, 128 * 3, 128, 128));
		_Weapon_ShootBow_AnimationUp_Right.addFrame(sf::IntRect(128 * 29, 128 * 3, 128, 128));
		_Weapon_ShootBow_AnimationUp_Right.addFrame(sf::IntRect(128 * 30, 128 * 3, 128, 128));
		_Weapon_ShootBow_AnimationUp_Right.addFrame(sf::IntRect(128 * 31, 128 * 3, 128, 128));
		_Weapon_ShootBow_AnimationDown_Left.setSpriteSheet(*_textureWeapon);
		_Weapon_ShootBow_AnimationDown_Left.addFrame(sf::IntRect(128 * 28, 128 * 7, 128, 128));
		_Weapon_ShootBow_AnimationDown_Left.addFrame(sf::IntRect(128 * 29, 128 * 7, 128, 128));
		_Weapon_ShootBow_AnimationDown_Left.addFrame(sf::IntRect(128 * 30, 128 * 7, 128, 128));
		_Weapon_ShootBow_AnimationDown_Left.addFrame(sf::IntRect(128 * 31, 128 * 7, 128, 128));
		_Weapon_ShootBow_AnimationDown_Right.setSpriteSheet(*_textureWeapon);
		_Weapon_ShootBow_AnimationDown_Right.addFrame(sf::IntRect(128 * 28, 128 * 5, 128, 128));
		_Weapon_ShootBow_AnimationDown_Right.addFrame(sf::IntRect(128 * 29, 128 * 5, 128, 128));
		_Weapon_ShootBow_AnimationDown_Right.addFrame(sf::IntRect(128 * 30, 128 * 5, 128, 128));
		_Weapon_ShootBow_AnimationDown_Right.addFrame(sf::IntRect(128 * 31, 128 * 5, 128, 128));
	}
}
