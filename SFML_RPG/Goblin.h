#pragma once
#include "Enemy.h"

class Enemy;
class Goblin : public Enemy
{
public:
	Goblin(sf::Vector2f position, sf::Texture* texture);
	~Goblin();

	void update(sf::Time _deltaTime);
	void render(sf::RenderWindow &_window);
	void processEvents(sf::Event &event);

private:
	void setAnimationState();
	void setAnimations();

	void classAI();

	void initTextures();

private:

	enum AnimationType
	{
		Standing = 0,   // 4
		Hopping = 4,    // 8
		Charging = 12,  // 8
		Attacking = 20, // 4
		Throwing = 24,  // 4
		Blocking = 28,  // 2
		TakingHit = 30, // 4
		Dying = 34,     // 6
		CritDying = 40, // 8
	};

	AnimationType _ActionType;
};

