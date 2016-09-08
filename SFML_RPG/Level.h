#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Game.h"

using namespace std;

class Level : public sf::Drawable, public sf::Transformable
{
public:
	Level(sf::Texture * texture);
	~Level();

	void load(string path, sf::Vector2i size);//, const int* tiles);
	void render(sf::RenderWindow &_window);
	void printMap();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::Texture* _texture;

	int _map[10][10];

	sf::Vector2i _tileSize;
	sf::Vector2i _mapSize;
	sf::VertexArray _vertices;
};

