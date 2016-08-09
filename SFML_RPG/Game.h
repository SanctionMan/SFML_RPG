#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "CollisionSystem.h"
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"


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

private:

	float _frameTime = 1.0f / 60.0f;
	sf::Time _elapsedTime;

	sf::RenderWindow _window;

	TextureManager _TextureManager;

	std::vector<Entity*> _entities;
};

