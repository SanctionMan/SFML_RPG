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

void CollisionSystem::check(std::vector<Entity*> &_entities)
{
	// Check Circle vs Circle Collision 
	for (unsigned int i = 0; i < _entities.size(); i++)
	{
		for (unsigned int j = 0; j < _entities.size(); j++)
		{
			if (j == i)
				continue;

			//Variables!
			float xd = _entities[i]->_position.x - _entities[j]->_position.x;
			float yd = _entities[i]->_position.y - _entities[j]->_position.y;
			float radA = _entities[i]->_radius;
			float radB = _entities[j]->_radius;
			float distance = sqrt((xd * xd) + (yd * yd));

			//Collision!
			if (distance < radA + radB)
			{
				//Resolve Collision!


				float overlap = (radA + radB) - distance;
				sf::Vector2f direction = _entities[i]->_position - _entities[j]->_position;
				sf::Vector2f newdirection = normalize(direction) * (overlap / 2) * (_entities[j]->_mass / (_entities[i]->_mass + _entities[j]->_mass));
				sf::Vector2f newdirectionB = normalize(direction) * (overlap / 2) * (_entities[i]->_mass / (_entities[j]->_mass + _entities[i]->_mass));
				//cout << newdirection.x << newdirection.y << endl;
				//Move Entities
				_entities[i]->_shape.move(newdirection);
				_entities[j]->_shape.move((-newdirectionB));
			}

		}

	}
}

sf::Vector2f CollisionSystem::normalize(sf::Vector2f &vector)
{
	float length = sqrt(vector.x * vector.x + vector.y * vector.y);

	if (length != 0) {
		vector.x = vector.x / length;
		vector.y = vector.y / length;
	}

	return vector;
}
