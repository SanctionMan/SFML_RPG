#include "CollisionSystem.h"



CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::update(std::vector<Entity*>& _entities)
{
	// Check Entity Collision and stop movement
	for (unsigned int i = 0; i < _entities.size(); i++)
	{
		sf::FloatRect bounds = _entities[i]->_bounds.getGlobalBounds();
		for (unsigned int j = 0; j < _entities.size(); j++)
		{
			if (j == i)
				continue;

			sf::FloatRect intersect;
			if (bounds.intersects(_entities[j]->_bounds.getGlobalBounds(), intersect))
			{
				sf::Vector2f pos = _entities[i]->_bounds.getPosition();
				if (intersect.width > intersect.height)
				{
					if (pos.y > intersect.top)
					{
						_entities[i]->_bounds.move(0, intersect.height);

					}
					else
					{
						_entities[i]->_bounds.move(0, -intersect.height);

					}

				}
				else
				{
					if (pos.x > intersect.left)
					{
						_entities[i]->_bounds.move(intersect.width, 0);

					}
					else
					{
						_entities[i]->_bounds.move(-intersect.width, 0);

					}

				}

			}

		}

	}
}
