#include "CollisionSystem.h"



CollisionSystem::CollisionSystem()
{
}


CollisionSystem::~CollisionSystem()
{
}

void CollisionSystem::update(std::vector<Entity*> _entities, int _collisionDetail, sf::Vector2u _resolution)
{
	_collisionDetailStored = _collisionDetail;

	gridWidthTemp = _resolution.x / (_collisionDetail);
	gridHeightTemp = _resolution.y / (_collisionDetail);

	int lastHeight, lastWidth;
	collisionChecks = 0;

	for (int x = 0; x < _collisionDetail + 1; x++)
	{
		for (int y = 0; y < _collisionDetail + 1; y++)
		{
			for (Entity* ent : _entities)
			{
				bool didPush = false;
				if (ent->_position.x < gridWidthTemp * x && ent->_position.x > lastWidth)
				{
					if (ent->_position.y < gridHeightTemp * y && ent->_position.y > lastHeight)
					{
						currentGrid.push_back(ent);
						didPush = true;
					}
				}
				
				lastWidth = gridWidthTemp * (x - 1);
				lastHeight = gridHeightTemp * y;

				//float distance = CalculateDistance(sf::Vector2f(ent->_position.x, ent->_position.y), sf::Vector2f(
				//	gridWidthTemp, gridHeightTemp));
				//float distanced = CalculateDistance(sf::Vector2f(ent->_position.x, ent->_position.y), sf::Vector2f(
				//	lastWidth, lastHeight));
				//distance = distanced / distance;

				//cout << distance << endl;

				//if(!didPush)
				//{
				//	currentGrid.push_back(ent);
				//}
			}

			//DEBUG GRID TOOL
			if (x == 2 && y == 3) {
				currentX = x;
				currentY = y;
				for (Entity* ent : currentGrid)
				{
					ent->_bounds.setOutlineColor(sf::Color::Red);
				}
			}//DEBUG GRID TOOL

			gridSize = currentGrid.size();
			check();

			currentGrid.clear();
		}
	}
}

void CollisionSystem::check()
{
	if(gridSize <= 1)
	{
		return;
	}
	collisionChecks++;

	// Check Circle vs Circle Collision 
	for (unsigned int i = 0; i < currentGrid.size(); i++)
	{
		for (unsigned int j = 0; j < currentGrid.size(); j++)
		{
			if (j == i)
				continue;

			//Variables!
			float xd = currentGrid[i]->_position.x - currentGrid[j]->_position.x;
			float yd = currentGrid[i]->_position.y - currentGrid[j]->_position.y;
			float radA = currentGrid[i]->_radius;
			float radB = currentGrid[j]->_radius;
			float distance = sqrt((xd * xd) + (yd * yd));

			//Collision!
			if (distance < radA + radB)
			{
				//Resolve Collision!

				float overlap = (radA + radB) - distance;
				sf::Vector2f direction = currentGrid[i]->_position - currentGrid[j]->_position;
				sf::Vector2f newdirection = normalize(direction) * (overlap / 2) * (currentGrid[j]->_mass / (currentGrid[i]->_mass + currentGrid[j]->_mass));
				sf::Vector2f newdirectionB = normalize(direction) * (overlap / 2) * (currentGrid[i]->_mass / (currentGrid[j]->_mass + currentGrid[i]->_mass));
				//cout << newdirection.x << newdirection.y << endl;
				//Move Entities
				currentGrid[i]->_bounds.move(newdirection);
				currentGrid[j]->_bounds.move((-newdirectionB));
			}
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
			vert1.color = sf::Color::Black;
			vert2.color = sf::Color::Black;
			vert3.color = sf::Color::Black;
			vert4.color = sf::Color::Black;

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



sf::Vector2f CollisionSystem::normalize(sf::Vector2f &vector)
{
	float length = sqrt(vector.x * vector.x + vector.y * vector.y);

	if (length != 0) {
		vector.x = vector.x / length;
		vector.y = vector.y / length;
	}

	return vector;
}
