#pragma once

#include "Game.h"

class Entity;
class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void update(std::vector<Entity*> &_entities);
	void check(std::vector<Entity*> &_entities);

	sf::Vector2f normalize(sf::Vector2f &vector);
};

