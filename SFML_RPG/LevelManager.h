#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Game.h"

using namespace std;

class LevelManager : public sf::Drawable, public sf::Transformable
{
public:
	LevelManager(sf::Texture * texture);
	~LevelManager();

	void load(string path);
	void render(sf::RenderWindow &_window);
	void printMap();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:

	void loadMapData();
	bool loadMapLayers(string &line, string &type);

	void setupMapVertices(string layer);

private:

	enum {
		size
	};

	bool _isFloorLoaded = false;
	bool _isLayerLoaded = false;

	sf::Texture* _texture;

	int _map[10][10];
	int _layer2[10][10];


	sf::Vector2i _tileSize;
	sf::Vector2i _mapSize;
	sf::VertexArray _vertices;
	sf::VertexArray _vertices2;

	int _lineNumber = 0;
	string _filepath;
};

