#include "Game.h"

Game* gameHandle = 0;

float CalculateDistance(sf::Vector2f a, sf::Vector2f b)
{
	float diffy = a.y - b.y;
	float diffx = a.x - b.x;
	return sqrt(((diffy * diffy) + (diffy * diffy)) + ((diffx * diffx) + (diffx * diffx)));
}

Game::Game()
{
	_window = new sf::RenderWindow(sf::VideoMode(1280, 800), "SFML_RPG");
	gameHandle = this;
}

Game::~Game()
{
	_window->close();
	delete _window;
}

void Game::Run()
{
	//Init Game
	init();

	//Init collision
	_CollisionSystem = new CollisionSystem();

	int perFrameCollision = 0;
	sf::Clock clock;
	_elapsedTime = clock.getElapsedTime();
	while (_window->isOpen())
	{
		_elapsedTime += clock.restart();
		while (_elapsedTime.asSeconds() > _frameTime)
		{
			handleInput();
			update(_elapsedTime);
			
			_elapsedTime = clock.restart();
		}
		_CollisionSystem->check(_entities, 6, _window->getSize());

		render();
	}
}

sf::RenderWindow* Game::GetWindow()
{
	return _window;
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
	_TextureManager->loadTexture("steel_armor.png", "Resources/Textures/Entities/Player/steel_armor.png");// Player Body
	_TextureManager->loadTexture("male_head1.png", "Resources/Textures/Entities/Player/male_head1.png");// Player Head
	//Enemy
	_TextureManager->loadTexture("goblin.png", "Resources/Textures/Entities/Enemy/goblin.png");// Goblin

	if (!font.loadFromFile("Resources/Fonts/Atarian/SF Atarian System.ttf"))
	{
		cout << "Loading font = error" << endl;
	}
	text.setFont(font);

	//Show Textures that are loaded into memory
	_TextureManager->showTexturesList();

	//Test tile parser! maps! wicked! anus!
	_tileParser = new TileParser();
	_tileParser->textureManager = _TextureManager;
	_tileParser->Init("Maps/Map_001.txt");
	_tileParser->Parse();

	//Create Player and Set Texture
	createEntity(new Player(sf::Vector2f(100, 100), _TextureManager->getTexture("male_head1.png"), 
													_TextureManager->getTexture("steel_armor.png")));
	createEntity(new Goblin(sf::Vector2f(150, 150), _TextureManager->getTexture("goblin.png")));

}

void Game::handleInput()
{
	sf::Event event;
	while (_window->pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			_window->close();
			break;
		case sf::Event::Resized:
			break;
		case sf::Event::KeyPressed:
			processEntities(event);
			break;
		case sf::Event::KeyReleased:
			processEntities(event);
			break;
		case sf::Event::MouseButtonPressed:
			mouseClicks(event);
			break;
		case sf::Event::MouseButtonReleased:
			break;
		}
	}
}

void Game::update(sf::Time ElapsedTime)
{
	updateEntities();
	mousePosition = sf::Vector2f(sf::Mouse::getPosition(*_window).x, sf::Mouse::getPosition(*_window).y);

	string printMe =  "Entity Count: " + std::to_string(_entities.size()) + "\n";
	printMe += "Collision Grid Info: X=" + std::to_string(_CollisionSystem->currentX) + " Y=" + std::to_string(_CollisionSystem->currentY)
		+ " EntityCount=" + std::to_string(_CollisionSystem->gridSize);

	text.setString(printMe);
	text.setFillColor(sf::Color::Black);
}

void Game::render()
{
	_window->clear(sf::Color::Magenta);
	//Draw map
	for(std::pair<int, Tile*> tile : _tileParser->tileID)
	{
		tile.second->render(*_window);
	}
	//Draw Entities
	renderEntities();

	//Draw collision grid
	_CollisionSystem->drawGrid();

	//Draw UI
	_window->draw(text);
	_window->display();
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
		it->render(*_window);
	}
}

void Game::processEntities(sf::Event &event)
{
	for (auto &it : _entities)
	{
		it->processEvents(event);
	}
}

void Game::mouseClicks(sf::Event& event)
{
	switch (event.mouseButton.button)
	{
	case sf::Mouse::Left:
		break;
	case sf::Mouse::Right:
		createEntity(new Goblin(sf::Vector2f(mousePosition), _TextureManager->getTexture("goblin.png")));
		break;
	case sf::Mouse::Middle:
		break;
	}
}

sf::RenderWindow* GetGameWindow()
{
	return gameHandle->_window;
}

Player* GetPlayer()
{
	//Loop through entities. ent = entity;
	for(Entity* ent : gameHandle->_entities)
	{
		//If this is player, go in here and return it!
		if(ent->_name == "Player")
		{
			return (Player*)ent; //can cast to player because player inherits from entity.
		}
	}

	//Return null if nothing is there...
	return 0;
}
