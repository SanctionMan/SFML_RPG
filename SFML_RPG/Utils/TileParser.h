#pragma once

#include "../GlobalRPG.hpp"


class Tile
{
public:
	Tile(sf::Texture* texture, sf::Vector2f position);
	~Tile();


	void render(sf::RenderWindow &_window);
	void processEvents(sf::Event &event);

	sf::Vector2f _position;
	sf::RectangleShape _tile;
};

class TileParser
{
public:
	TileParser();
	~TileParser();

	bool Init(string file);
	bool Parse();

	map<int, Tile*> tileID;
	TextureManager* textureManager;
	int mapArray[10][10];
private:
	string fileContents;
protected:
	string filePath;
};