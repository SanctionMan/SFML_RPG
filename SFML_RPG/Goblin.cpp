#include "Goblin.h"



Goblin::Goblin(sf::Vector2f position, sf::Texture* texture)
{
	constructEnemy(position, sf::Vector2f(128, 128), texture, sf::Vector2f(0, -30));
	// Set textures & frames for animations
	initTextures();
	// Create pointer to current animation
	_currentAnimationBody = &_Animations["_Body_Standing_AnimationDown"];
	// Setup animatedsprite
	_name = "Goblin";
}


Goblin::~Goblin()
{
}

void Goblin::update(sf::Time _deltaTime)
{
	// Enemy class updates
	enemyUpdate(_deltaTime);

	// class specific AI
	classAI();

	// Set Animation State
	setAnimationState();

	// Set Animations
	setAnimations();
}

void Goblin::render(sf::RenderWindow& _window)
{
	enemyRender(_window);

}

void Goblin::processEvents(sf::Event& event)
{
	enemyProcessEvents(event);
}

void Goblin::setAnimationState()
{
	// Set Standing Action
	if (!_isRunning)
	{
		_ActionType = Standing;
		_isStanding = true;
	}
	else _isStanding = false;
	// Set Running Action
	if (_isRunning)
	{
		_ActionType = Charging;
	}



	// Set Attacking Action
	if (_isAttacking && !_isRunning)
	{
		_ActionType = Attacking;
	}

	// Set Charging Action
	if (_isCharging && !_isRunning)
	{
		_ActionType = Charging;
	}

	// Set Dying Action
	if (_health <= 0)
	{
		_ActionType = Dying;
	}
}

void Goblin::setAnimations()
{
	switch (_ActionType)
	{
	case Standing:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationUp"];
			break;
		case Down:
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationDown"];
			break;
		case Left:
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationLeft"];
			break;
		case Right:
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationRight"];
			break;
		case Up_Left:
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedBody.setFrameTime(sf::seconds(0.2f));
			_currentAnimationBody = &_Animations["_Body_Standing_AnimationDown_Right"];
			break;
		}
		break;
	case Hopping:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Hopping_AnimationUp"];
			break;
		case Down:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Hopping_AnimationDown"];
			break;
		case Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Hopping_AnimationLeft"];
			break;
		case Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Hopping_AnimationRight"];
			break;
		case Up_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Hopping_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Hopping_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Hopping_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Hopping_AnimationDown_Right"];
			break;
		}
		break;
	case Charging:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Charging_AnimationUp"];
			break;
		case Down:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Charging_AnimationDown"];
			break;
		case Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Charging_AnimationLeft"];
			break;
		case Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Charging_AnimationRight"];
			break;
		case Up_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Charging_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Charging_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Charging_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Charging_AnimationDown_Right"];
			break;
		}
		break;
	case Attacking:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationUp"];
			break;
		case Down:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationDown"];
			break;
		case Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationLeft"];
			break;
		case Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationRight"];
			break;
		case Up_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Attacking_AnimationDown_Right"];
			break;
		}
		break;
	case Throwing:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Throwing_AnimationUp"];
			break;
		case Down:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Throwing_AnimationDown"];
			break;
		case Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Throwing_AnimationLeft"];
			break;
		case Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Throwing_AnimationRight"];
			break;
		case Up_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Throwing_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Throwing_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Throwing_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Throwing_AnimationDown_Right"];
			break;
		}
		break;
	case Blocking:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationUp"];
			break;
		case Down:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationDown"];
			break;
		case Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationLeft"];
			break;
		case Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationRight"];
			break;
		case Up_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Blocking_AnimationDown_Right"];
			break;
		}
		break;
	case TakingHit:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationUp"];
			break;
		case Down:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationDown"];
			break;
		case Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationLeft"];
			break;
		case Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationRight"];
			break;
		case Up_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationDown_Left"];
			break;
		case Down_Right:

			_animatedBody.setFrameTime(sf::seconds(0.1f));

			_currentAnimationBody = &_Animations["_Body_TakingHit_AnimationDown_Right"];

			break;
		}
		break;
	case Dying:
		switch (_lastAnimationDirection)
		{
		case Up:		
			_animatedBody.setFrameTime(sf::seconds(0.1f));		
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationUp"];	
			break;
		case Down:
			_animatedBody.setFrameTime(sf::seconds(0.1f));				
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationDown"];			
			break;
		case Left:			
			_animatedBody.setFrameTime(sf::seconds(0.1f));			
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationLeft"];			
			break;
		case Right:			
			_animatedBody.setFrameTime(sf::seconds(0.1f));	
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationRight"];	
			break;
		case Up_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationUp_Left"];
			break;
		case Up_Right:	
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_Dying_AnimationDown_Right"];
			break;
		}
		break;
	case CritDying:
		switch (_lastAnimationDirection)
		{
		case Up:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_CritDying_AnimationUp"];
			break;
		case Down:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_CritDying_AnimationDown"];
			break;
		case Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_CritDying_AnimationLeft"];
			break;
		case Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_CritDying_AnimationRight"];
			break;
		case Up_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_CritDying_AnimationUp_Left"];
			break;
		case Up_Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_CritDying_AnimationUp_Right"];
			break;
		case Down_Left:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_CritDying_AnimationDown_Left"];
			break;
		case Down_Right:
			_animatedBody.setFrameTime(sf::seconds(0.1f));
			_currentAnimationBody = &_Animations["_Body_CritDying_AnimationDown_Right"];
			break;
		}
		break;
	}
}

void Goblin::classAI()
{
	if (_isCharging)
		_speed = 500;
	else
		_speed = 150;
	if (_distance < 200 && _distance > 100)
	{
		_isRunning = false;
		_isCharging = true;
	}
	else
		_isCharging = false;
}

void Goblin::initTextures()
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

	// Hopping (8 frames)
	{	// Set texture for each animation
		_Animations["_Body_Hopping_AnimationUp"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Hopping_AnimationDown"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Hopping_AnimationLeft"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Hopping_AnimationRight"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Hopping_AnimationUp_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Hopping_AnimationUp_Right"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Hopping_AnimationDown_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Hopping_AnimationDown_Right"].setSpriteSheet(*_textureBody);
		for (int a = 0; a < 8; a++)
		{	// Set each frame for animations
			_Animations["_Body_Hopping_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Hopping), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Body_Hopping_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Hopping), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Body_Hopping_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Hopping), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Hopping_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Hopping), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Hopping_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Hopping), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Hopping_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Hopping), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Hopping_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Hopping), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Hopping_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Hopping), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}

	// Charging (8 frames)
	{	// Set texture for each animation
		_Animations["_Body_Charging_AnimationUp"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Charging_AnimationDown"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Charging_AnimationLeft"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Charging_AnimationRight"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Charging_AnimationUp_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Charging_AnimationUp_Right"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Charging_AnimationDown_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Charging_AnimationDown_Right"].setSpriteSheet(*_textureBody);
		for (int a = 0; a < 8; a++)
		{	// Set each frame for animations
			_Animations["_Body_Charging_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Charging), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Body_Charging_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Charging), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Body_Charging_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Charging), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Charging_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Charging), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Charging_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Charging), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Charging_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Charging), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Charging_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Charging), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Charging_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Charging), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
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

	// Throwing(spear) (4 frames)
	{	// Set texture for each animation
		_Animations["_Body_Throwing_AnimationUp"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Throwing_AnimationDown"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Throwing_AnimationLeft"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Throwing_AnimationRight"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Throwing_AnimationUp_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Throwing_AnimationUp_Right"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Throwing_AnimationDown_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Throwing_AnimationDown_Right"].setSpriteSheet(*_textureBody);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Body_Throwing_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + Throwing), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Body_Throwing_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + Throwing), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Body_Throwing_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + Throwing), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Throwing_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + Throwing), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Throwing_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Throwing), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Throwing_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Throwing), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_Throwing_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + Throwing), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_Throwing_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + Throwing), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
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

	// Dying (6 Frames)
	{	// Set texture for each animation
		_Animations["_Body_Dying_AnimationUp"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Dying_AnimationDown"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Dying_AnimationLeft"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Dying_AnimationRight"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Dying_AnimationUp_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Dying_AnimationUp_Right"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Dying_AnimationDown_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_Dying_AnimationDown_Right"].setSpriteSheet(*_textureBody);
		for (int a = 0; a < 6; a++)
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

	// CritDying (8 Frames)
	{	// Set texture for each animation
		_Animations["_Body_CritDying_AnimationUp"].setSpriteSheet(*_textureBody);
		_Animations["_Body_CritDying_AnimationDown"].setSpriteSheet(*_textureBody);
		_Animations["_Body_CritDying_AnimationLeft"].setSpriteSheet(*_textureBody);
		_Animations["_Body_CritDying_AnimationRight"].setSpriteSheet(*_textureBody);
		_Animations["_Body_CritDying_AnimationUp_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_CritDying_AnimationUp_Right"].setSpriteSheet(*_textureBody);
		_Animations["_Body_CritDying_AnimationDown_Left"].setSpriteSheet(*_textureBody);
		_Animations["_Body_CritDying_AnimationDown_Right"].setSpriteSheet(*_textureBody);
		for (int a = 0; a < 4; a++)
		{	// Set each frame for animations
			_Animations["_Body_CritDying_AnimationUp"].addFrame(sf::IntRect(_animationSize.x * (a + CritDying), _animationSize.x * Up, _animationSize.x, _animationSize.x));
			_Animations["_Body_CritDying_AnimationDown"].addFrame(sf::IntRect(_animationSize.x * (a + CritDying), _animationSize.x * Down, _animationSize.x, _animationSize.x));
			_Animations["_Body_CritDying_AnimationLeft"].addFrame(sf::IntRect(_animationSize.x * (a + CritDying), _animationSize.x * Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_CritDying_AnimationRight"].addFrame(sf::IntRect(_animationSize.x * (a + CritDying), _animationSize.x * Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_CritDying_AnimationUp_Left"].addFrame(sf::IntRect(_animationSize.x * (a + CritDying), _animationSize.x * Up_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_CritDying_AnimationUp_Right"].addFrame(sf::IntRect(_animationSize.x * (a + CritDying), _animationSize.x * Up_Right, _animationSize.x, _animationSize.x));
			_Animations["_Body_CritDying_AnimationDown_Left"].addFrame(sf::IntRect(_animationSize.x * (a + CritDying), _animationSize.x * Down_Left, _animationSize.x, _animationSize.x));
			_Animations["_Body_CritDying_AnimationDown_Right"].addFrame(sf::IntRect(_animationSize.x * (a + CritDying), _animationSize.x * Down_Right, _animationSize.x, _animationSize.x));
		}
	}
}

