#include "CollisionSystem.h"
#include <list>



CollisionSystem::CollisionSystem():
	_mapSize(100,100),
	_grid(sf::Lines, 2)
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
			//if (x == 2 && y == 3) {
			//	currentX = x;
			//	currentY = y;
			//	for (Entity* ent : currentGrid)
			//	{
			//		ent->_bounds.setOutlineColor(sf::Color::Red);
			//	}
			//}//DEBUG GRID TOOL

			gridSize = currentGrid.size();

			currentGrid.clear();
			check();
		}
	}
}

void CollisionSystem::update2(std::vector<Entity*> _entities)
{
	registerEntitys(_entities);
	collisionChecks = 0;

	for (int i = 0; i < _cols * _rows; i++)
	{
		if (_buckets[i].size() > 1)
		{
			for (auto ent : _buckets[i])
			{
				currentGrid.push_back(ent);
			}
		}

	}

	gridSize = currentGrid.size();
	check();
	currentGrid.clear();
	clearBuckets();
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
				//Move Entities
				currentGrid[i]->_bounds.move(newdirection);
				currentGrid[j]->_bounds.move((-newdirectionB));
			}
		}
	}
}

void CollisionSystem::drawGrid()
{
	
	GetGameWindow()->draw(_grid);	
	
	//for (int x = 0; x < _collisionDetailStored + 1; x++)
	//{
	//	for (int y = 0; y < _collisionDetailStored + 1; y++)
	//	{
	//		//x = (x == 0) ? 1 : x;
	//		int width = gridWidthTemp * x;
	//		int xPos = 0;
	//		//y = (y == 0) ? 1 : y;
	//		int height = gridHeightTemp * y;
	//		int yPos = 0;
	//		sf::Vector2f vec1(x, height);
	//		sf::Vector2f vec2(width, height);
	//		sf::Vertex vert1(vec1);
	//		sf::Vertex vert2(vec2);
	//		sf::Vector2f vec3(width, height);
	//		sf::Vector2f vec4(width, yPos);
	//		sf::Vertex vert3(vec3);
	//		sf::Vertex vert4(vec4);
	//		vert1.color = sf::Color::Black;
	//		vert2.color = sf::Color::Black;
	//		vert3.color = sf::Color::Black;
	//		vert4.color = sf::Color::Black;
	//		//gridLines.push_back(vert1);
	//		//gridLines.push_back(vert2);
	//		grid.append(vert1);
	//		grid.append(vert2);
	//		//GetGameWindow()->draw(&gridLines[0], 2, sf::Lines);
	//		//gridLines.clear();
	//		//gridLines.push_back(vert3);
	//		//gridLines.push_back(vert4);
	//		grid.append(vert3);
	//		grid.append(vert4);
	//		//GetGameWindow()->draw(&gridLines[0], 2, sf::Lines);
	//		//gridLines.clear();
	//	}
	//}
	//GetGameWindow()->draw(grid);
	//cout << grid.getVertexCount() << endl;
}

void CollisionSystem::loadGrid(sf::Vector2i _mapSize)
{
	//Create Vertexs
	sf::Vertex vertex1;
	sf::Vertex vertex2;
	sf::Vertex vertex3;
	sf::Vertex vertex4;
	//Calculate number of lines
	_cols = (_mapSize.x / _cellSize);
	_rows = (_mapSize.y / _cellSize);

	int lines = 0;
	for (int x = 0; x <= _cols; x++)
	{
		for (int y = 0; y <= _rows; y++)
		{
			//Create horizontal line
			vertex1.position = sf::Vector2f(0, y * _cellSize);
			vertex1.color = sf::Color::Black;
			vertex2.position = sf::Vector2f(_mapSize.x, y * _cellSize);
			vertex2.color = sf::Color::Black;

			//Create vertical line
			vertex3.position = sf::Vector2f(y * _cellSize, 0);
			vertex3.color = sf::Color::Black;
			vertex4.position = sf::Vector2f(y * _cellSize, _mapSize.y);
			vertex4.color = sf::Color::Black;

			//Add Lines to grid
			_grid.append(vertex1);
			_grid.append(vertex2);
			_grid.append(vertex3);
			_grid.append(vertex4);

			lines += 2; //Count the number of lines added to grid
		}
	}
	//Resize grid to fit the number of lines
	_grid.resize(lines);
	//cout << lines << endl;
	//cout << grid.getVertexCount() << endl;


	//setup number of buckets
	for (int i = 0; i < _cols * _rows; i++)
	{
		_buckets[i];
		_numberOfBuckets++;
	}
}

void CollisionSystem::registerEntitys(std::vector<Entity*> _entities)
{
	for (auto ent : _entities)
	{
		vector<int> Ent_ID = getEntitiesIDs(ent);
		for (auto id : Ent_ID)
		{
			_buckets[id].push_back(ent);
			//cout << "Check: " << id << endl;
		}
	}
}

void CollisionSystem::clearBuckets()
{
	_buckets.clear();
	_numberOfBuckets = 0;
	for (int i = 0; i < _cols * _rows; i++)
	{
		_buckets[i];
		_numberOfBuckets++;
	}
}

void CollisionSystem::addBucket(sf::Vector2f vector, float width, std::vector<int> &list)
{
	
	int cellPosition = (int)((floor(vector.x / _cellSize)) + (floor(vector.y / _cellSize)) * width);
	cout << cellPosition << endl;
	if (!contains(list, cellPosition))
		list.push_back(cellPosition);
}

vector<int> CollisionSystem::getEntitiesIDs(Entity* ent)
{
	vector<int> listID;

	sf::Vector2f min = sf::Vector2f(ent->_position.x - ent->_radius, ent->_position.y - ent->_radius);
	sf::Vector2f max = sf::Vector2f(ent->_position.x + ent->_radius, ent->_position.y + ent->_radius);

	float width = _mapSize.x / _cellSize;
	//TopLeft
	addBucket(min, width, listID);
	//TopRight
	addBucket(sf::Vector2f(max.x, min.y), width, listID);
	//BottomRight
	addBucket(sf::Vector2f(max.x, max.y), width, listID);
	//BottomLeft
	addBucket(sf::Vector2f(min.x, max.y), width, listID);

	return listID;
}

bool CollisionSystem::contains(std::vector<int> list, int cell_ID)
{
	std::vector<int>::iterator it;
	it = find(list.begin(), list.end(), cell_ID);
	if (it != list.end())
		return true;
	else
		return false;
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

