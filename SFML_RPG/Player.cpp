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
	updateMovement(_deltaTime);

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
	setAnimationState();
	setAnimations();

	//if (!_isMovingUp && !_isMovingDown && !_isMovingLeft && !_isMovingRight)
	//{
	//	switch (_lastAnimationDirection)
	//	{
	//	case Up:
	//		_animatedHead.setFrameTime(sf::seconds(0.3f));
	//		_animatedBody.setFrameTime(sf::seconds(0.3f));
	//		_animatedWeapon.setFrameTime(sf::seconds(0.3f));
	//		_currentAnimationHead = &_Animations["_Head_Standing_AnimationUp"];
	//		_currentAnimationBody = &_Animations["_Body_Standing_AnimationUp"];
	//		_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationUp"];
	//		break;
	//	case Down:
	//		_animatedHead.setFrameTime(sf::seconds(0.3f));
	//		_animatedBody.setFrameTime(sf::seconds(0.3f));
	//		_animatedWeapon.setFrameTime(sf::seconds(0.3f));
	//		_currentAnimationHead = &_Animations["_Head_Standing_AnimationDown"];
	//		_currentAnimationBody = &_Animations["_Body_Standing_AnimationDown"];
	//		_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationDown"];
	//		break;
	//	case Left:
	//		_animatedHead.setFrameTime(sf::seconds(0.3f));
	//		_animatedBody.setFrameTime(sf::seconds(0.3f));
	//		_animatedWeapon.setFrameTime(sf::seconds(0.3f));
	//		_currentAnimationHead = &_Animations["_Head_Standing_AnimationLeft"];
	//		_currentAnimationBody = &_Animations["_Body_Standing_AnimationLeft"];
	//		_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationLeft"];
	//		break;
	//	case Right:
	//		_animatedHead.setFrameTime(sf::seconds(0.3f));
	//		_animatedBody.setFrameTime(sf::seconds(0.3f));
	//		_animatedWeapon.setFrameTime(sf::seconds(0.3f));
	//		_currentAnimationHead = &_Animations["_Head_Standing_AnimationRight"];
	//		_currentAnimationBody = &_Animations["_Body_Standing_AnimationRight"];
	//		_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationRight"];
	//		break;
	//	case Up_Left:
	//		_animatedHead.setFrameTime(sf::seconds(0.3f));
	//		_animatedBody.setFrameTime(sf::seconds(0.3f));
	//		_animatedWeapon.setFrameTime(sf::seconds(0.3f));
	//		_currentAnimationHead = &_Animations["_Head_Standing_AnimationUp_Left"];
	//		_currentAnimationBody = &_Animations["_Body_Standing_AnimationUp_Left"];
	//		_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationUp_Left"];
	//		break;
	//	case Up_Right:
	//		_animatedHead.setFrameTime(sf::seconds(0.3f));
	//		_animatedBody.setFrameTime(sf::seconds(0.3f));
	//		_animatedWeapon.setFrameTime(sf::seconds(0.3f));
	//		_currentAnimationHead = &_Animations["_Head_Standing_AnimationUp_Right"];
	//		_currentAnimationBody = &_Animations["_Body_Standing_AnimationUp_Right"];
	//		_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationUp_Right"];
	//		break;
	//	case Down_Left:
	//		_animatedHead.setFrameTime(sf::seconds(0.3f));
	//		_animatedBody.setFrameTime(sf::seconds(0.3f));
	//		_animatedWeapon.setFrameTime(sf::seconds(0.3f));
	//		_currentAnimationHead = &_Animations["_Head_Standing_AnimationDown_Left"];
	//		_currentAnimationBody = &_Animations["_Body_Standing_AnimationDown_Left"];
	//		_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationDown_Left"];
	//		break;
	//	case Down_Right:
	//		_animatedHead.setFrameTime(sf::seconds(0.3f));
	//		_animatedBody.setFrameTime(sf::seconds(0.3f));
	//		_animatedWeapon.setFrameTime(sf::seconds(0.3f));
	//		_currentAnimationHead = &_Animations["_Head_Standing_AnimationDown_Right"];
	//		_currentAnimationBody = &_Animations["_Body_Standing_AnimationDown_Right"];
	//		_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationDown_Right"];
	//		break;
	//	}
	//
	//}
	//if (_isMovingUp)
	//{
	//	_animatedHead.setFrameTime(sf::seconds(0.1f));
	//	_animatedBody.setFrameTime(sf::seconds(0.1f));
	//	_animatedWeapon.setFrameTime(sf::seconds(0.1f));
	//	_currentAnimationHead = &_Animations["_Head_Running_AnimationUp"];
	//	_currentAnimationBody = &_Animations["_Body_Running_AnimationUp"];
	//	_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationUp"];
	//	_lastAnimationDirection = Up;
	//}
	//if (_isMovingDown)
	//{
	//	_animatedHead.setFrameTime(sf::seconds(0.1f));
	//	_animatedBody.setFrameTime(sf::seconds(0.1f));
	//	_animatedWeapon.setFrameTime(sf::seconds(0.1f));
	//	_currentAnimationHead = &_Animations["_Head_Running_AnimationDown"];
	//	_currentAnimationBody = &_Animations["_Body_Running_AnimationDown"];
	//	_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationDown"];
	//	_lastAnimationDirection = Down;
	//}
	//if (_isMovingLeft)
	//{
	//	_animatedHead.setFrameTime(sf::seconds(0.1f));
	//	_animatedBody.setFrameTime(sf::seconds(0.1f));
	//	_animatedWeapon.setFrameTime(sf::seconds(0.1f));
	//	_currentAnimationHead = &_Animations["_Head_Running_AnimationLeft"];
	//	_currentAnimationBody = &_Animations["_Body_Running_AnimationLeft"];
	//	_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationLeft"];
	//	_lastAnimationDirection = Left;
	//}
	//if (_isMovingRight)
	//{
	//	_animatedHead.setFrameTime(sf::seconds(0.1f));
	//	_animatedBody.setFrameTime(sf::seconds(0.1f));
	//	_animatedWeapon.setFrameTime(sf::seconds(0.1f));
	//	_currentAnimationHead = &_Animations["_Head_Running_AnimationRight"];
	//	_currentAnimationBody = &_Animations["_Body_Running_AnimationRight"];
	//	_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationRight"];
	//	_lastAnimationDirection = Right;
	//}
	//if (_isMovingUp && _isMovingLeft)
	//{
	//	_animatedHead.setFrameTime(sf::seconds(0.1f));
	//	_animatedBody.setFrameTime(sf::seconds(0.1f));
	//	_animatedWeapon.setFrameTime(sf::seconds(0.1f));
	//	_currentAnimationHead = &_Animations["_Head_Running_AnimationUp_Left"];
	//	_currentAnimationBody = &_Animations["_Body_Running_AnimationUp_Left"];
	//	_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationUp_Left"];
	//	_lastAnimationDirection = Up_Left;
	//}
	//if (_isMovingUp && _isMovingRight)
	//{
	//	_animatedHead.setFrameTime(sf::seconds(0.1f));
	//	_animatedBody.setFrameTime(sf::seconds(0.1f));
	//	_animatedWeapon.setFrameTime(sf::seconds(0.1f));
	//	_currentAnimationHead = &_Animations["_Head_Running_AnimationUp_Right"];
	//	_currentAnimationBody = &_Animations["_Body_Running_AnimationUp_Right"];
	//	_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationUp_Right"];
	//	_lastAnimationDirection = Up_Right;
	//}
	//if (_isMovingDown && _isMovingLeft)
	//{
	//	_animatedHead.setFrameTime(sf::seconds(0.1f));
	//	_animatedBody.setFrameTime(sf::seconds(0.1f));
	//	_animatedWeapon.setFrameTime(sf::seconds(0.1f));
	//	_currentAnimationHead = &_Animations["_Head_Running_AnimationDown_Left"];
	//	_currentAnimationBody = &_Animations["_Body_Running_AnimationDown_Left"];
	//	_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationDown_Left"];
	//	_lastAnimationDirection = Down_Left;
	//}
	//if (_isMovingDown && _isMovingRight)
	//{
	//	_animatedHead.setFrameTime(sf::seconds(0.1f));
	//	_animatedBody.setFrameTime(sf::seconds(0.1f));
	//	_animatedWeapon.setFrameTime(sf::seconds(0.1f));
	//	_currentAnimationHead = &_Animations["_Head_Running_AnimationDown_Right"];
	//	_currentAnimationBody = &_Animations["_Body_Running_AnimationDown_Right"];
	//	_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationDown_Right"];
	//	_lastAnimationDirection = Down_Right;
	//}
	//if (_isAttacking)
	//{
	//	_animatedHead.setFrameTime(sf::seconds(0.1f));
	//	_animatedBody.setFrameTime(sf::seconds(0.1f));
	//	_animatedWeapon.setFrameTime(sf::seconds(0.1f));
	//	_currentAnimationHead = &_Animations["_Head_Attacking_AnimationRight"];
	//	_currentAnimationBody = &_Animations["_Body_Attacking_AnimationRight"];
	//	_currentAnimationWeapon = &_Animations["_Weapon_Attacking_AnimationRight"];
	//}
	//if (_isCasting)
	//{
	//	_animatedHead.setFrameTime(sf::seconds(0.1f));
	//	_animatedBody.setFrameTime(sf::seconds(0.1f));
	//	_animatedWeapon.setFrameTime(sf::seconds(0.1f));
	//	_currentAnimationHead = &_Animations["_Head_Casting_AnimationRight"];
	//	_currentAnimationBody = &_Animations["_Body_Casting_AnimationRight"];
	//	_currentAnimationWeapon = &_Animations["_Weapon_Casting_AnimationRight"];
	//}

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

	_healthBar.render(_window);
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

void Player::setAnimationState()
{
	// Set Standing Action
	if (!_isMovingUp && !_isMovingDown && !_isMovingLeft && !_isMovingRight)
	{
		_ActionType = Standing;
		_isStanding = true;
	}
	else _isStanding = false;
	// Set Running Action
	if (_isMovingUp || _isMovingDown || _isMovingLeft || _isMovingRight)
	{
		_isRunning = true;
	}
	else
		_isRunning = false;
	// set action and direction
	if (_isMovingUp)
	{
		_ActionType = Running;
		_lastAnimationDirection = Up;
	}
	if (_isMovingDown)
	{
		_ActionType = Running;
		_lastAnimationDirection = Down;
	}
	if (_isMovingLeft)
	{
		_ActionType = Running;
		_lastAnimationDirection = Left;
	}
	if (_isMovingRight)
	{
		_ActionType = Running;
		_lastAnimationDirection = Right;
	}
	if (_isMovingUp && _isMovingLeft)
	{
		_ActionType = Running;
		_lastAnimationDirection = Up_Left;
	}
	if (_isMovingUp && _isMovingRight)
	{
		_ActionType = Running;
		_lastAnimationDirection = Up_Right;
	}
	if (_isMovingDown && _isMovingLeft)
	{
		_ActionType = Running;
		_lastAnimationDirection = Down_Left;
	}
	if (_isMovingDown && _isMovingRight)
	{
		_ActionType = Running;
		_lastAnimationDirection = Down_Right;
	}

	// Set Attacking Action
	if (_isAttacking && !_isRunning)
	{
		_ActionType = Attacking;
	}

	// Set Casting Action
	if (_isCasting && !_isRunning)
	{
		_ActionType = Casting;
	}

	// Set Shooting Action
	if (_isCasting && !_isRunning)
	{
		_ActionType = Shooting;
	}

	// Set Blocking Action
	if (_isCasting && !_isRunning)
	{
		_ActionType = Blocking;
	}

	// Set TakingHit Action
	if (_isCasting && !_isRunning)
	{
		_ActionType = TakingHit;
	}

	// Set Dying Action
	if (_health <= 0)
	{
		_ActionType = Dying;
	}
}

void Player::setAnimations()
{
	switch (_ActionType)
	{
	case Standing:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedHead.setFrameTime(sf::seconds(0.2f));
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_animatedWeapon.setFrameTime(sf::seconds(0.2f));
			_currentAnimationHead = &_Animations["_Head_Standing_AnimationUp"];
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationUp"];
			_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationUp"];
			break;
		case Down:
			_animatedHead.setFrameTime(sf::seconds(0.2f));
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_animatedWeapon.setFrameTime(sf::seconds(0.2f));
			_currentAnimationHead = &_Animations["_Head_Standing_AnimationDown"];
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationDown"];
			_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationDown"];
			break;
		case Left:
			_animatedHead.setFrameTime(sf::seconds(0.2f));
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_animatedWeapon.setFrameTime(sf::seconds(0.2f));
			_currentAnimationHead = &_Animations["_Head_Standing_AnimationLeft"];
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationLeft"];
			_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationLeft"];
			break;
		case Right:
			_animatedHead.setFrameTime(sf::seconds(0.2f));
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_animatedWeapon.setFrameTime(sf::seconds(0.2f));
			_currentAnimationHead = &_Animations["_Head_Standing_AnimationRight"];
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationRight"];
			_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationRight"];
			break;
		case Up_Left:
			_animatedHead.setFrameTime(sf::seconds(0.2f));
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_animatedWeapon.setFrameTime(sf::seconds(0.2f));
			_currentAnimationHead = &_Animations["_Head_Standing_AnimationUp_Left"];
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationUp_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedHead.setFrameTime(sf::seconds(0.2f));
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_animatedWeapon.setFrameTime(sf::seconds(0.2f));
			_currentAnimationHead = &_Animations["_Head_Standing_AnimationUp_Right"];
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationUp_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedHead.setFrameTime(sf::seconds(0.2f));
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_animatedWeapon.setFrameTime(sf::seconds(0.2f));
			_currentAnimationHead = &_Animations["_Head_Standing_AnimationDown_Left"];
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationDown_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedHead.setFrameTime(sf::seconds(0.2f));
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_animatedWeapon.setFrameTime(sf::seconds(0.2f));
			_currentAnimationHead = &_Animations["_Head_Standing_AnimationDown_Right"];
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationDown_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationDown_Right"];
			break;
		}
		break;
	case Running:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Running_AnimationUp"];
			_currentAnimationBody = &_Animations["_Body_Running_AnimationUp"];
			_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationUp"];
			break;
		case Down:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Running_AnimationDown"];
			_currentAnimationBody = &_Animations["_Body_Running_AnimationDown"];
			_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationDown"];
			break;
		case Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Running_AnimationLeft"];
			_currentAnimationBody = &_Animations["_Body_Running_AnimationLeft"];
			_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationLeft"];
			break;
		case Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Running_AnimationRight"];
			_currentAnimationBody = &_Animations["_Body_Running_AnimationRight"];
			_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationRight"];
			break;
		case Up_Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Running_AnimationUp_Left"];
			_currentAnimationBody = &_Animations["_Body_Running_AnimationUp_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Running_AnimationUp_Right"];
			_currentAnimationBody = &_Animations["_Body_Running_AnimationUp_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Running_AnimationDown_Left"];
			_currentAnimationBody = &_Animations["_Body_Running_AnimationDown_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Running_AnimationDown_Right"];
			_currentAnimationBody = &_Animations["_Body_Running_AnimationDown_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_Running_AnimationDown_Right"];
			break;
		}
		break;
	case Attacking:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Attacking_AnimationUp"];
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationUp"];
			_currentAnimationWeapon = &_Animations["_Weapon_Attacking_AnimationUp"];
			break;
		case Down:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Attacking_AnimationDown"];
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationDown"];
			_currentAnimationWeapon = &_Animations["_Weapon_Attacking_AnimationDown"];
			break;
		case Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Attacking_AnimationLeft"];
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationLeft"];
			_currentAnimationWeapon = &_Animations["_Weapon_Attacking_AnimationLeft"];
			break;
		case Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Attacking_AnimationRight"];
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationRight"];
			_currentAnimationWeapon = &_Animations["_Weapon_Attacking_AnimationRight"];
			break;
		case Up_Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Attacking_AnimationUp_Left"];
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationUp_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_Attacking_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Attacking_AnimationUp_Right"];
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationUp_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_Attacking_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Attacking_AnimationDown_Left"];
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationDown_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_Attacking_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Attacking_AnimationDown_Right"];
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationDown_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_Attacking_AnimationDown_Right"];
			break;
		}
		break;
	case Casting:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Casting_AnimationUp"];
			_currentAnimationBody = &_Animations["_Body_Casting_AnimationUp"];
			_currentAnimationWeapon = &_Animations["_Weapon_Casting_AnimationUp"];
			break;
		case Down:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Casting_AnimationDown"];
			_currentAnimationBody = &_Animations["_Body_Casting_AnimationDown"];
			_currentAnimationWeapon = &_Animations["_Weapon_Casting_AnimationDown"];
			break;
		case Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Casting_AnimationLeft"];
			_currentAnimationBody = &_Animations["_Body_Casting_AnimationLeft"];
			_currentAnimationWeapon = &_Animations["_Weapon_Casting_AnimationLeft"];
			break;
		case Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Casting_AnimationRight"];
			_currentAnimationBody = &_Animations["_Body_Casting_AnimationRight"];
			_currentAnimationWeapon = &_Animations["_Weapon_Casting_AnimationRight"];
			break;
		case Up_Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Casting_AnimationUp_Left"];
			_currentAnimationBody = &_Animations["_Body_Casting_AnimationUp_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_Casting_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Casting_AnimationUp_Right"];
			_currentAnimationBody = &_Animations["_Body_Casting_AnimationUp_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_Casting_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Casting_AnimationDown_Left"];
			_currentAnimationBody = &_Animations["_Body_Casting_AnimationDown_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_Casting_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Casting_AnimationDown_Right"];
			_currentAnimationBody = &_Animations["_Body_Casting_AnimationDown_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_Casting_AnimationDown_Right"];
			break;
		}
		break;
	case Shooting:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Shooting_AnimationUp"];
			_currentAnimationBody = &_Animations["_Body_Shooting_AnimationUp"];
			_currentAnimationWeapon = &_Animations["_Weapon_Shooting_AnimationUp"];
			break;
		case Down:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Shooting_AnimationDown"];
			_currentAnimationBody = &_Animations["_Body_Shooting_AnimationDown"];
			_currentAnimationWeapon = &_Animations["_Weapon_Shooting_AnimationDown"];
			break;
		case Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Shooting_AnimationLeft"];
			_currentAnimationBody = &_Animations["_Body_Shooting_AnimationLeft"];
			_currentAnimationWeapon = &_Animations["_Weapon_Shooting_AnimationLeft"];
			break;
		case Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Shooting_AnimationRight"];
			_currentAnimationBody = &_Animations["_Body_Shooting_AnimationRight"];
			_currentAnimationWeapon = &_Animations["_Weapon_Shooting_AnimationRight"];
			break;
		case Up_Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Shooting_AnimationUp_Left"];
			_currentAnimationBody = &_Animations["_Body_Shooting_AnimationUp_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_Shooting_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Shooting_AnimationUp_Right"];
			_currentAnimationBody = &_Animations["_Body_Shooting_AnimationUp_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_Shooting_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Shooting_AnimationDown_Left"];
			_currentAnimationBody = &_Animations["_Body_Shooting_AnimationDown_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_Shooting_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Shooting_AnimationDown_Right"];
			_currentAnimationBody = &_Animations["_Body_Shooting_AnimationDown_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_Shooting_AnimationDown_Right"];
			break;
		}
		break;
	case Blocking:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Blocking_AnimationUp"];
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationUp"];
			_currentAnimationWeapon = &_Animations["_Weapon_Blocking_AnimationUp"];
			break;
		case Down:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Blocking_AnimationDown"];
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationDown"];
			_currentAnimationWeapon = &_Animations["_Weapon_Blocking_AnimationDown"];
			break;
		case Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Blocking_AnimationLeft"];
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationLeft"];
			_currentAnimationWeapon = &_Animations["_Weapon_Blocking_AnimationLeft"];
			break;
		case Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Blocking_AnimationRight"];
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationRight"];
			_currentAnimationWeapon = &_Animations["_Weapon_Blocking_AnimationRight"];
			break;
		case Up_Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Blocking_AnimationUp_Left"];
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationUp_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_Blocking_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Blocking_AnimationUp_Right"];
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationUp_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_Blocking_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Blocking_AnimationDown_Left"];
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationDown_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_Blocking_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Blocking_AnimationDown_Right"];
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationDown_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_Blocking_AnimationDown_Right"];
			break;
		}
		break;
	case TakingHit:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_TakingHit_AnimationUp"];
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationUp"];
			_currentAnimationWeapon = &_Animations["_Weapon_TakingHit_AnimationUp"];
			break;
		case Down:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_TakingHit_AnimationDown"];
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationDown"];
			_currentAnimationWeapon = &_Animations["_Weapon_TakingHit_AnimationDown"];
			break;
		case Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_TakingHit_AnimationLeft"];
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationLeft"];
			_currentAnimationWeapon = &_Animations["_Weapon_TakingHit_AnimationLeft"];
			break;
		case Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_TakingHit_AnimationRight"];
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationRight"];
			_currentAnimationWeapon = &_Animations["_Weapon_TakingHit_AnimationRight"];
			break;
		case Up_Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_TakingHit_AnimationUp_Left"];
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationUp_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_TakingHit_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_TakingHit_AnimationUp_Right"];
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationUp_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_TakingHit_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_TakingHit_AnimationDown_Left"];
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationDown_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_TakingHit_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_TakingHit_AnimationDown_Right"];
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationDown_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_TakingHit_AnimationDown_Right"];
			break;
		}
		break;
	case Dying:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Dying_AnimationUp"];
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationUp"];
			_currentAnimationWeapon = &_Animations["_Weapon_Dying_AnimationUp"];
			break;
		case Down:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Dying_AnimationDown"];
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationDown"];
			_currentAnimationWeapon = &_Animations["_Weapon_Dying_AnimationDown"];
			break;
		case Left:			
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Dying_AnimationLeft"];
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationLeft"];
			_currentAnimationWeapon = &_Animations["_Weapon_Dying_AnimationLeft"];
			break;
		case Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Dying_AnimationRight"];
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationRight"];
			_currentAnimationWeapon = &_Animations["_Weapon_Dying_AnimationRight"];
			break;
		case Up_Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Dying_AnimationUp_Left"];
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationUp_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_Dying_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Dying_AnimationUp_Right"];
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationUp_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_Dying_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Dying_AnimationDown_Left"];
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationDown_Left"];
			_currentAnimationWeapon = &_Animations["_Weapon_Dying_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedHead.setFrameTime(sf::seconds(0.1f));
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_animatedWeapon.setFrameTime(sf::seconds(0.1f));
			_currentAnimationHead = &_Animations["_Head_Dying_AnimationDown_Right"];
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationDown_Right"];
			_currentAnimationWeapon = &_Animations["_Weapon_Dying_AnimationDown_Right"];
			break;
		}
		break;
	}
}

void Player::updateMovement(sf::Time _deltaTime)
{
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
}

void Player::initPlayerTextures()
{
	// Set textures & frames for animations
	initHeadTextures();
	initBodyTextures();
	initWeaponTextures();

	// Create pointer to current animation
	_currentAnimationHead = &_Animations["_Head_Standing_AnimationDown"];
	_currentAnimationBody = &_Animations["_Body_Standing_AnimationDown"];
	_currentAnimationWeapon = &_Animations["_Weapon_Standing_AnimationDown"];

	// Setup animatedsprite
	_animatedHead.setPosition(_position + _adjustment_xy);
	_animatedBody.setPosition(_position + _adjustment_xy);
	_animatedWeapon.setPosition(_position + _adjustment_xy);
}

void Player::initHeadTextures()
{
	// Standing (4 frames)
	{	// Set texture for each animation
		_Animations["_Head_Standing_AnimationUp"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Standing_AnimationDown"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Standing_AnimationLeft"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Standing_AnimationRight"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Standing_AnimationUp_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Standing_AnimationUp_Right"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Standing_AnimationDown_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Standing_AnimationDown_Right"].setSpriteSheet(*_textureHead);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Head_Standing_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Head_Standing_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Head_Standing_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Standing_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_Standing_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Standing_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_Standing_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Standing_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Running (8 frames)
	{	// Set texture for each animation
		_Animations["_Head_Running_AnimationUp"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Running_AnimationDown"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Running_AnimationLeft"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Running_AnimationRight"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Running_AnimationUp_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Running_AnimationUp_Right"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Running_AnimationDown_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Running_AnimationDown_Right"].setSpriteSheet(*_textureHead);
		for (int a = 0; a < 8; a++)
		{	// Set each frame for animations
			_Animations["_Head_Running_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Head_Running_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Head_Running_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Running_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_Running_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Running_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_Running_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Running_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Attacking (4 frames)
	{	// Set texture for each animation
		_Animations["_Head_Attacking_AnimationUp"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Attacking_AnimationDown"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Attacking_AnimationLeft"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Attacking_AnimationRight"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Attacking_AnimationUp_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Attacking_AnimationUp_Right"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Attacking_AnimationDown_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Attacking_AnimationDown_Right"].setSpriteSheet(*_textureHead);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Head_Attacking_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Head_Attacking_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Head_Attacking_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Attacking_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_Attacking_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Attacking_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_Attacking_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Attacking_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Casting (4 frames)
	{	// Set texture for each animation
		_Animations["_Head_Casting_AnimationUp"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Casting_AnimationDown"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Casting_AnimationLeft"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Casting_AnimationRight"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Casting_AnimationUp_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Casting_AnimationUp_Right"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Casting_AnimationDown_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Casting_AnimationDown_Right"].setSpriteSheet(*_textureHead);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Head_Casting_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Head_Casting_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Head_Casting_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Casting_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_Casting_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Casting_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_Casting_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Casting_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Shooting(bow) (4 frames)
	{	// Set texture for each animation
		_Animations["_Head_Shooting_AnimationUp"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Shooting_AnimationDown"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Shooting_AnimationLeft"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Shooting_AnimationRight"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Shooting_AnimationUp_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Shooting_AnimationUp_Right"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Shooting_AnimationDown_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Shooting_AnimationDown_Right"].setSpriteSheet(*_textureHead);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Head_Shooting_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Head_Shooting_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Head_Shooting_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Shooting_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_Shooting_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Shooting_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_Shooting_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Shooting_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Blocking (2 frames)
	{	// Set texture for each animation
		_Animations["_Head_Blocking_AnimationUp"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Blocking_AnimationDown"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Blocking_AnimationLeft"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Blocking_AnimationRight"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Blocking_AnimationUp_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Blocking_AnimationUp_Right"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Blocking_AnimationDown_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Blocking_AnimationDown_Right"].setSpriteSheet(*_textureHead);
		for (int a = 0; a < 2; a++)
		{	// Set each frame for animations
			_Animations["_Head_Blocking_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Head_Blocking_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Head_Blocking_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Blocking_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_Blocking_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Blocking_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_Blocking_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Blocking_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// TakingHit (2 frames)
	{	// Set texture for each animation
		_Animations["_Head_TakingHit_AnimationUp"].setSpriteSheet(*_textureHead);
		_Animations["_Head_TakingHit_AnimationDown"].setSpriteSheet(*_textureHead);
		_Animations["_Head_TakingHit_AnimationLeft"].setSpriteSheet(*_textureHead);
		_Animations["_Head_TakingHit_AnimationRight"].setSpriteSheet(*_textureHead);
		_Animations["_Head_TakingHit_AnimationUp_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_TakingHit_AnimationUp_Right"].setSpriteSheet(*_textureHead);
		_Animations["_Head_TakingHit_AnimationDown_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_TakingHit_AnimationDown_Right"].setSpriteSheet(*_textureHead);
		for (int a = 0; a < 2; a++)
		{	// Set each frame for animations
			_Animations["_Head_TakingHit_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Head_TakingHit_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Head_TakingHit_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_TakingHit_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_TakingHit_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_TakingHit_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_TakingHit_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_TakingHit_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Dying (4 Frames)
	{	// Set texture for each animation
		_Animations["_Head_Dying_AnimationUp"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Dying_AnimationDown"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Dying_AnimationLeft"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Dying_AnimationRight"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Dying_AnimationUp_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Dying_AnimationUp_Right"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Dying_AnimationDown_Left"].setSpriteSheet(*_textureHead);
		_Animations["_Head_Dying_AnimationDown_Right"].setSpriteSheet(*_textureHead);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Head_Dying_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Head_Dying_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Head_Dying_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Dying_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_Dying_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Dying_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Head_Dying_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Head_Dying_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}
}

void Player::initBodyTextures()
{
	// Standing (4 frames)
	{	// Set texture for each animation
		_Animations["_Body_Standing_AnimationUp"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Standing_AnimationDown"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Standing_AnimationLeft"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Standing_AnimationRight"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Standing_AnimationUp_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Standing_AnimationUp_Right"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Standing_AnimationDown_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Standing_AnimationDown_Right"].setSpriteSheet(*_textureBody);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Body_Standing_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Body_Standing_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Body_Standing_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Standing_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Standing_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Standing_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Standing_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Standing_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
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
			_Animations["_Body_Running_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Body_Running_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Body_Running_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Running_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Running_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Running_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Running_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Running_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Attacking (4 frames)
	{	// Set texture for each animation
		_Animations["_Body_Attacking_AnimationUp"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Attacking_AnimationDown"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Attacking_AnimationLeft"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Attacking_AnimationRight"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Attacking_AnimationUp_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Attacking_AnimationUp_Right"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Attacking_AnimationDown_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Attacking_AnimationDown_Right"].setSpriteSheet(*_textureBody);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Body_Attacking_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Body_Attacking_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Body_Attacking_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Attacking_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Attacking_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Attacking_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Attacking_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Attacking_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Casting (4 frames)
	{	// Set texture for each animation
		_Animations["_Body_Casting_AnimationUp"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Casting_AnimationDown"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Casting_AnimationLeft"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Casting_AnimationRight"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Casting_AnimationUp_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Casting_AnimationUp_Right"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Casting_AnimationDown_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Casting_AnimationDown_Right"].setSpriteSheet(*_textureBody);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Body_Casting_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Body_Casting_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Body_Casting_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Casting_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Casting_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Casting_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Casting_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Casting_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Shooting(bow) (4 frames)
	{	// Set texture for each animation
		_Animations["_Body_Shooting_AnimationUp"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Shooting_AnimationDown"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Shooting_AnimationLeft"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Shooting_AnimationRight"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Shooting_AnimationUp_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Shooting_AnimationUp_Right"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Shooting_AnimationDown_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Shooting_AnimationDown_Right"].setSpriteSheet(*_textureBody);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Body_Shooting_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Body_Shooting_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Body_Shooting_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Shooting_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Shooting_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Shooting_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Shooting_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Shooting_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Blocking (2 frames)
	{	// Set texture for each animation
		_Animations["_Body_Blocking_AnimationUp"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Blocking_AnimationDown"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Blocking_AnimationLeft"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Blocking_AnimationRight"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Blocking_AnimationUp_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Blocking_AnimationUp_Right"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Blocking_AnimationDown_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Blocking_AnimationDown_Right"].setSpriteSheet(*_textureBody);
		for (int a = 0; a < 2; a++)
		{	// Set each frame for animations
			_Animations["_Body_Blocking_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Body_Blocking_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Body_Blocking_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Blocking_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Blocking_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Blocking_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Blocking_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Blocking_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// TakingHit (2 frames)
	{	// Set texture for each animation
		_Animations["_Body_TakingHit_AnimationUp"].setSpriteSheet(*_textureBody);
		_Animations["_Body_TakingHit_AnimationDown"].setSpriteSheet(*_textureBody);
		_Animations["_Body_TakingHit_AnimationLeft"].setSpriteSheet(*_textureBody);
		_Animations["_Body_TakingHit_AnimationRight"].setSpriteSheet(*_textureBody);
		_Animations["_Body_TakingHit_AnimationUp_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_TakingHit_AnimationUp_Right"].setSpriteSheet(*_textureBody);
		_Animations["_Body_TakingHit_AnimationDown_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_TakingHit_AnimationDown_Right"].setSpriteSheet(*_textureBody);
		for (int a = 0; a < 2; a++)
		{	// Set each frame for animations
			_Animations["_Body_TakingHit_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Body_TakingHit_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Body_TakingHit_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_TakingHit_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_TakingHit_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_TakingHit_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_TakingHit_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_TakingHit_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Dying (4 Frames)
	{	// Set texture for each animation
		_Animations["_Body_Dying_AnimationUp"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Dying_AnimationDown"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Dying_AnimationLeft"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Dying_AnimationRight"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Dying_AnimationUp_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Dying_AnimationUp_Right"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Dying_AnimationDown_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Dying_AnimationDown_Right"].setSpriteSheet(*_textureBody);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Body_Dying_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Body_Dying_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Body_Dying_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Dying_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Dying_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Dying_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Dying_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Dying_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}
}

void Player::initWeaponTextures()
{
	// Standing (4 frames)
	{	// Set texture for each animation
		_Animations["_Weapon_Standing_AnimationUp"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Standing_AnimationDown"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Standing_AnimationLeft"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Standing_AnimationRight"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Standing_AnimationUp_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Standing_AnimationUp_Right"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Standing_AnimationDown_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Standing_AnimationDown_Right"].setSpriteSheet(*_textureWeapon);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Weapon_Standing_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Standing_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Standing_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Standing_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Standing_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Standing_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Standing_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Standing_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Standing), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Running (8 frames)
	{	// Set texture for each animation
		_Animations["_Weapon_Running_AnimationUp"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Running_AnimationDown"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Running_AnimationLeft"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Running_AnimationRight"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Running_AnimationUp_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Running_AnimationUp_Right"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Running_AnimationDown_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Running_AnimationDown_Right"].setSpriteSheet(*_textureWeapon);
		for (int a = 0; a < 8; a++)
		{	// Set each frame for animations
			_Animations["_Weapon_Running_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Running_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Running_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Running_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Running_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Running_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Running_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Running_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Running), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Attacking (4 frames)
	{	// Set texture for each animation
		_Animations["_Weapon_Attacking_AnimationUp"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Attacking_AnimationDown"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Attacking_AnimationLeft"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Attacking_AnimationRight"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Attacking_AnimationUp_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Attacking_AnimationUp_Right"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Attacking_AnimationDown_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Attacking_AnimationDown_Right"].setSpriteSheet(*_textureWeapon);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Weapon_Attacking_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Attacking_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Attacking_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Attacking_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Attacking_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Attacking_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Attacking_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Attacking_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Attacking), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Casting (4 frames)
	{	// Set texture for each animation
		_Animations["_Weapon_Casting_AnimationUp"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Casting_AnimationDown"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Casting_AnimationLeft"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Casting_AnimationRight"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Casting_AnimationUp_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Casting_AnimationUp_Right"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Casting_AnimationDown_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Casting_AnimationDown_Right"].setSpriteSheet(*_textureWeapon);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Weapon_Casting_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Casting_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Casting_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Casting_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Casting_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Casting_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Casting_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Casting_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Casting), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Shooting(bow) (4 frames)
	{	// Set texture for each animation
		_Animations["_Weapon_Shooting_AnimationUp"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Shooting_AnimationDown"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Shooting_AnimationLeft"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Shooting_AnimationRight"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Shooting_AnimationUp_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Shooting_AnimationUp_Right"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Shooting_AnimationDown_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Shooting_AnimationDown_Right"].setSpriteSheet(*_textureWeapon);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Weapon_Shooting_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Shooting_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Shooting_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Shooting_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Shooting_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Shooting_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Shooting_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Shooting_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Shooting), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Blocking (2 frames)
	{	// Set texture for each animation
		_Animations["_Weapon_Blocking_AnimationUp"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Blocking_AnimationDown"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Blocking_AnimationLeft"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Blocking_AnimationRight"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Blocking_AnimationUp_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Blocking_AnimationUp_Right"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Blocking_AnimationDown_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Blocking_AnimationDown_Right"].setSpriteSheet(*_textureWeapon);
		for (int a = 0; a < 2; a++)
		{	// Set each frame for animations
			_Animations["_Weapon_Blocking_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Blocking_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Blocking_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Blocking_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Blocking_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Blocking_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Blocking_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Blocking_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Blocking), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// TakingHit (2 frames)
	{	// Set texture for each animation
		_Animations["_Weapon_TakingHit_AnimationUp"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_TakingHit_AnimationDown"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_TakingHit_AnimationLeft"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_TakingHit_AnimationRight"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_TakingHit_AnimationUp_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_TakingHit_AnimationUp_Right"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_TakingHit_AnimationDown_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_TakingHit_AnimationDown_Right"].setSpriteSheet(*_textureWeapon);
		for (int a = 0; a < 2; a++)
		{	// Set each frame for animations
			_Animations["_Weapon_TakingHit_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_TakingHit_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_TakingHit_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_TakingHit_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_TakingHit_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_TakingHit_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_TakingHit_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_TakingHit_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + TakingHit), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Dying (4 Frames)
	{	// Set texture for each animation
		_Animations["_Weapon_Dying_AnimationUp"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Dying_AnimationDown"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Dying_AnimationLeft"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Dying_AnimationRight"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Dying_AnimationUp_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Dying_AnimationUp_Right"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Dying_AnimationDown_Left"].setSpriteSheet(*_textureWeapon);
		_Animations["_Weapon_Dying_AnimationDown_Right"].setSpriteSheet(*_textureWeapon);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Weapon_Dying_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Dying_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Dying_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Dying_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Dying_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Dying_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Dying_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Weapon_Dying_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Dying), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}
}
