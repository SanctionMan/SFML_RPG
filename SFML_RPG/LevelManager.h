#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Game.h"

using namespace std;

class LevelManager
{
public:
	LevelManager(sf::Texture *texture);
	~LevelManager();

	void load(string path);
	void renderFloor(sf::RenderWindow &_window);
	void renderLayer1(sf::RenderWindow &_window);
	void printMap();

private:

	void loadMapData();
	bool loadMapLayers(string &line, string &type);

	template <size_t rows, size_t cols>
	void setupMapVertices(int (&_mapArray)[rows][cols], sf::VertexArray &_vertexArray);

private:

	const int test = 10;

	bool _isFloorLoaded = false;
	bool _isLayerLoaded = false;

	sf::Texture* _texture;
	int *p_mapArray[10][10];
	int _floor[10][10];
	int _layer1[10][10];

	sf::VertexArray _floorVertices;
	sf::VertexArray _layer1Vertices;

	sf::Vector2i _mapSize;
	sf::Vector2i _tileSize;


	int _lineNumber = 0;
	string _filepath;
};

