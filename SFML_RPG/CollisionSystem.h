#pragma once

#include "Game.h"

class Entity;
class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void update(std::vector<Entity*> _entities, int _collisionDetail, sf::Vector2u _resolution);
	void check();
	void drawGrid();

	sf::Vector2f normalize(sf::Vector2f &vector);


	int gridWidthTemp;
	int collisionChecks;
	int gridHeightTemp;
	int _collisionDetailStored;

	vector<Entity*> currentGrid;
	vector<sf::Vertex> gridLines;
	int currentX, currentY, gridSize;


};

