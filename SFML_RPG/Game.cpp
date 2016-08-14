#include "Game.h"

Game::Game()
	: _window(sf::VideoMode(1280, 800), "SFML_RPG")
{
}

Game::~Game()
{
}

void Game::Run()
{
	//System Setup
	CollisionSystem _CollisionSystem;

	//Init Game
	init();

	sf::Clock clock;
	_elapsedTime = clock.getElapsedTime();
	while (_window.isOpen())
	{
		_elapsedTime += clock.restart();
		while (_elapsedTime.asSeconds() > _frameTime)
		{
			handleInput();
			update(_elapsedTime);
			_CollisionSystem.update(_entities);
			_elapsedTime = clock.restart();
		}
		render();
	}
}

sf::RenderWindow* Game::GetWindow()
{
	return &_window;
}

void Game::init()
{
	//_window.setFramerateLimit(60);

	//Load Textures 
	_TextureManager = new TextureManager();
	//Mushroom
	_TextureManager->loadTexture("Mushroom.png", "Resources/Textures/Entities/Misc/Mushroom.png");
	//Map
	_TextureManager->loadTexture("spr_tile_wall_top_left.png", "Resources/Textures/Map/spr_tile_wall_top_left.png");// Top Left Corner
	_TextureManager->loadTexture("spr_tile_wall_bottom_left.png", "Resources/Textures/Map/spr_tile_wall_bottom_left.png");// Bottom Left Corner
	_TextureManager->loadTexture("spr_tile_wall_top_right.png", "Resources/Textures/Map/spr_tile_wall_top_right.png");// Top Right Corner
	_TextureManager->loadTexture("spr_tile_wall_bottom_right", "Resources/Textures/Map/spr_tile_wall_bottom_right.png");// Bottom Right Corner
	_TextureManager->loadTexture("spr_tile_wall_top.png", "Resources/Textures/Map/spr_tile_wall_top.png");// Top/Bottom Wall
	_TextureManager->loadTexture("spr_tile_wall_side.png", "Resources/Textures/Map/spr_tile_wall_side.png");// Right/Left Wall 
	_TextureManager->loadTexture("spr_tile_floor_alt.png", "Resources/Textures/Map/spr_tile_floor_alt.png");// Floor Alt
	//Player
	_TextureManager->loadTexture("steel_armor.png", "Resources/Textures/Entities/Player/steel_armor.png");//Player Body
	_TextureManager->loadTexture("male_head1.png", "Resources/Textures/Entities/Player/male_head1.png");//Player Head

	//Show Textures that are loaded into memory
	_TextureManager->showTexturesList();

	//Test tile parser! maps! wicked! anus!
	_tileParser = new TileParser();
	_tileParser->textureManager = _TextureManager;
	_tileParser->Init("Maps/Map_001.txt");
	_tileParser->Parse();

	//Create Player and Set Texture
	createEntity(new Player(sf::Vector2f(100, 100), _TextureManager->getTexture("male_head1.png"), _TextureManager->getTexture("steel_armor.png")));
	createEntity(new Enemy(_TextureManager->getTexture("Mushroom.png"), sf::Vector2f(300, 300)));
}

void Game::handleInput()
{
	sf::Event event;
	while (_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			processEntities(event);
			break;
		case sf::Event::KeyReleased:
			processEntities(event);
			break;
		case sf::Event::Closed:
			_window.close();
			break;
		}
	}
}

void Game::update(sf::Time ElapsedTime)
{
	updateEntities();
}

void Game::render()
{
	_window.clear(sf::Color::White);
	//Draw map
	for(std::pair<int, Tile*> tile : _tileParser->tileID)
	{
		tile.second->render(_window);
	}
	//Draw Entities
	renderEntities();
	_window.display();
}

void Game::cleanUp()
{
	for (auto &it : _entities)
	{
		std::cout << "Entity: " << it->_name << " Deleted!" << std::endl;
		delete it;
	}
}

void Game::createEntity(Entity* ent)
{
	_entities.push_back(ent);
}

void Game::updateEntities()
{
	for (auto &it : _entities)
	{
		it->update(_elapsedTime);
	}
}

void Game::renderEntities()
{
	for (auto &it : _entities)
	{
		it->render(_window);
	}
}

void Game::processEntities(sf::Event &event)
{
	for (auto &it : _entities)
	{
		it->processEvents(event);
	}
}
