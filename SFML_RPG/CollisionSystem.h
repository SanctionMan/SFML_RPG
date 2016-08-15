#pragma once

#include "Game.h"

class Entity;
class CollisionSystem
{
public:
	CollisionSystem();
	~CollisionSystem();

	void update(std::vector<Entity*> _entities);
	void check(std::vector<Entity*> _entities, int _collisionDetail, sf::Vector2u _resolution);
	void drawGrid();
	void doCheck(vector<Entity*> _entities);

	int gridWidthTemp;
	int gridHeightTemp;
	int _collisionDetailStored;

	vector<Entity*> currentGrid;
	vector<sf::Vertex> gridLines;
	int currentX, currentY, gridSize;

	sf::Vector2f normalize(sf::Vector2f &vector);
};

