#pragma once

#include "Game.h"

class Entity;
class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void update(std::vector<Entity*> entities, int collisionDetail, sf::Vector2u resolution);
	void update2(std::vector<Entity*> entities);
	void check();
	void drawGrid();
	void loadGrid(sf::Vector2i mapSize);
	void registerEntitys(std::vector<Entity*> entities);
	void clearBuckets();
	void addBucket(sf::Vector2f vector, float width, std::vector<int> &list);
	vector<int> getEntitiesIDs(Entity* ent);
	bool contains(std::vector<int> list, int cell_ID);
	vector<int> getNearbyList(Entity* ent);

	sf::Vector2f normalize(sf::Vector2f &vector);
	//Matts

	int _cols;
	int _rows;
	int _cellSize = 250;
	sf::Vector2i _mapSize;
	sf::VertexArray _grid;
	map<int, vector<Entity*>> _buckets;

	int _numberOfBuckets = 0;

	int gridWidthTemp;
	int collisionChecks;
	int gridHeightTemp;
	int _collisionDetailStored;

	vector<Entity*> currentGrid;
	vector<sf::Vertex> gridLines;
	int currentX, currentY, gridSize;

};

