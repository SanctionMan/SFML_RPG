#pragma once

#include "Game.h"

class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void update(std::vector<Entity*> &_entities);

};

