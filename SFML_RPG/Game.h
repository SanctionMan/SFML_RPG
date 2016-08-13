#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "CollisionSystem.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "GlobalRPG.hpp"

class TileParser;
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
	void update(sf::Time ElapsedTime);
	void render();
	void cleanUp();

	void createEntity(Entity* ent);
	void updateEntities();
	void renderEntities();
	void processEntities(sf::Event &event);

	TextureManager* _TextureManager=nullptr;
private:
	float _frameTime = 0.1f / 60.0f;
	sf::Time _elapsedTime;

	sf::RenderWindow _window;

	TileParser* _tileParser=nullptr;

	
	std::vector<Entity*> _entities;
};

