#include "CollisionSystem.h"



CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}
// not quite working correctly!!!!!
void CollisionSystem::update(std::vector<Entity*> _entities)
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
				//Could be collision so dive deeper for more checks..
				//check(_entities);
				//cout << "COLLISION CHECK!" << endl;

			}

		}

	}
}

void CollisionSystem::check(std::vector<Entity*> _entities, int _collisionDetail, sf::Vector2u _resolution)
{
	_collisionDetailStored = _collisionDetail;

	gridWidthTemp = _resolution.x / (_collisionDetail);
	gridHeightTemp = _resolution.y / (_collisionDetail);

	int lastHeight, lastWidth;

	for (int x = 0; x < _collisionDetail + 1; x++)
	{
		bool checkOrNot = false;

		for (int y = 0; y < _collisionDetail + 1; y++)
		{
			for (Entity* ent : _entities)
			{
				if(ent->_name == "Player")
				{
					checkOrNot = true;
				}
			}

			//0(&*^(^&(^&
			if (x == 2 && y == 3) {
				currentX = x;
				currentY = y;
				for(Entity* ent : currentGrid)
				{
					ent->_bounds.setOutlineColor(sf::Color::Red);
				}
				gridSize = currentGrid.size();
			}//^&(^&(^&(^&(

			if(checkOrNot)
			{
				for (Entity* ent : _entities) 
				{
					if (ent->_position.x <= gridWidthTemp * x && ent->_position.x >= lastWidth)
					{
						if (ent->_position.y <= gridHeightTemp * y && ent->_position.y >= lastHeight)
						{
							currentGrid.push_back(ent);
						}
					}
				}
				doCheck(currentGrid);
			}

			lastWidth = gridWidthTemp * (x - 1);
			lastHeight = gridHeightTemp * y;
			currentGrid.clear();
		}
	}
}

void CollisionSystem::drawGrid()
{
	for (int x = 0; x < _collisionDetailStored + 1; x++)
	{
		for (int y = 0; y < _collisionDetailStored + 1; y++)
		{
			//x = (x == 0) ? 1 : x;
			int width = gridWidthTemp * x;
			int xPos = 0;

			//y = (y == 0) ? 1 : y;
			int height = gridHeightTemp * y;
			int yPos = 0;

			sf::Vector2f vec1(x, height);
			sf::Vector2f vec2(width, height);
			sf::Vertex vert1(vec1);
			sf::Vertex vert2(vec2);

			sf::Vector2f vec3(width, height);
			sf::Vector2f vec4(width, yPos);
			sf::Vertex vert3(vec3);
			sf::Vertex vert4(vec4);

			gridLines.push_back(vert1);
			gridLines.push_back(vert2);

			GetGameWindow()->draw(&gridLines[0], 2, sf::Lines);
			gridLines.clear();

			gridLines.push_back(vert3);
			gridLines.push_back(vert4);

			GetGameWindow()->draw(&gridLines[0], 2, sf::Lines);
			gridLines.clear();
		}
	}
}

void CollisionSystem::doCheck(vector<Entity*> _entities)
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
