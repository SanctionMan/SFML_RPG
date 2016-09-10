#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include <algorithm>

#include "TextureManager.h"
#include "CollisionSystem.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h" //Any class that inherits this needs to be included at bottom of this header.
#include "GlobalRPG.hpp"
#include "LevelManager.h"

float CalculateDistance(sf::Vector2f a, sf::Vector2f b);
class LevelManager;
class Player;
class TileParser;
class CollisionSystem;
class Game 
{
public:
	Game();
	~Game();

	void Run();
	sf::RenderWindow* GetWindow();
public:

	void init();
	void handleInput();
	void update(sf::Time _deltaTime);
	void render(LevelManager *level);
	void cleanUp();

	void createEntity(Entity* ent);
	void updateEntities();
	void renderEntities();
	void processEntities(sf::Event &event);

	void updateStatistics(sf::Time _deltaTime);

	void mouseClicks(sf::Event &event);

	TextureManager* _TextureManager = nullptr;
	LevelManager* _LevelManager;

	std::vector<Entity*> _entities;
	sf::Vector2f mousePosition;
	sf::RenderWindow* _window = nullptr;
private:
	//Time
	float _frameTime = 0.1f / 60.0f;
	sf::Time _deltaTime;

	bool _isGridActive = true;

	//Text
	sf::Time _updateTime;
	std::size_t _numFrames;
	sf::Font _font;
	sf::Text _FPS;
	sf::Text text;

	//Window 
	int _windowWidth;
	int _windowHeight;

	//Views
	sf::View _mainView;

	//System Setup
	CollisionSystem* _CollisionSystem;

	TileParser* _tileParser=nullptr;
};

sf::RenderWindow* GetGameWindow();
Player* GetPlayer();