#include "Game.h"

Game* gameHandle = 0;

float CalculateDistance(sf::Vector2f a, sf::Vector2f b)
{
	float diffy = a.y - b.y;
	float diffx = a.x - b.x;
	return sqrt(((diffy * diffy) + (diffy * diffy)) + ((diffx * diffx) + (diffx * diffx)));
}

Game::Game():
	_windowWidth(900),
	_windowHeight(600)
{
	_window = new sf::RenderWindow(sf::VideoMode(_windowWidth, _windowHeight), "SFML_RPG");
	gameHandle = this;
	_mainView.reset(sf::FloatRect(0, 0, _windowWidth, _windowHeight));
	_mainView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	_mainView.setCenter(_windowWidth / 2, _windowHeight / 2);
	//_mainView.rotate(45);
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

	//Init Level
	//_LevelManager = new LevelManager(_TextureManager->getTexture("grassland_tiles.png"));
	_LevelManager = new LevelManager(_TextureManager->getTexture("tiles_0.png"));
	_LevelManager->load("Maps/Map_001.txt");
	//_LevelManager->printMap();


	//Init collision
	_CollisionSystem = new CollisionSystem();
	_CollisionSystem->loadGrid(sf::Vector2i(50 * 64,50 * 32));

	sf::Clock clock;
	_deltaTime = clock.getElapsedTime();
	while (_window->isOpen())
	{
		_deltaTime += clock.restart();
		while (_deltaTime.asSeconds() >= _frameTime)
		{
			handleInput();
			update(_deltaTime);
			
			_deltaTime = clock.restart();
		}
		//_CollisionSystem->update(_entities, 8, _window->getSize());
		_CollisionSystem->update(_entities);
		_LevelManager->update(_deltaTime);

		render(_LevelManager);
	}
}

sf::RenderWindow* Game::GetWindow()
{
	return _window;
}

void Game::init()
{
	//_window->setFramerateLimit(60);

	//Load Textures 
	_TextureManager = new TextureManager();
	//Mushroom
	_TextureManager->loadTexture("Mushroom.png", "Resources/Textures/Entities/Misc/Mushroom.png");
	//Map
	//_TextureManager->loadTexture("grassland_tiles.png", "Resources/Textures/Map/Grass/grassland_tiles.png");// Sample tiles
	_TextureManager->loadTexture("tiles_0.png", "Resources/Textures/Map/tiles_0.png");

	//Player
	_TextureManager->loadTexture("steel_armor.png", "Resources/Textures/Entities/Player/steel_armor.png");// Player Body
	_TextureManager->loadTexture("male_head1.png", "Resources/Textures/Entities/Player/male_head1.png");// Player Head
	_TextureManager->loadTexture("greatsword.png", "Resources/Textures/Entities/Player/greatsword.png");// Player Head
	//Enemy
	_TextureManager->loadTexture("goblin.png", "Resources/Textures/Entities/Enemy/goblin.png");// Goblin
	//Load Fonts
	if (!_font.loadFromFile("Resources/Fonts/Atarian/SF Atarian System.ttf"))
	{
		cout << "Loading font = error" << endl;
	}
	//Set Text
	text.setFont(_font);
	_FPS.setFont(_font);
	_FPS.setPosition(500, 0);
	_FPS.setFillColor(sf::Color::Black);

	//Show Textures that are loaded into memory
	_TextureManager->showTexturesList();

	//Create Player and Set Texture
	createEntity(new Player(sf::Vector2f(250, 750), _TextureManager->getTexture("male_head1.png"), 
													_TextureManager->getTexture("steel_armor.png"),
													_TextureManager->getTexture("greatsword.png")));
	//createEntity(new Goblin(sf::Vector2f(150, 150), _TextureManager->getTexture("goblin.png")));

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
			if (event.key.code == sf::Keyboard::F3)
			{
				_isGridActive = !_isGridActive;
			}
			break;
		case sf::Event::KeyReleased:
			processEntities(event);
			break;
		case sf::Event::MouseButtonPressed:
			mouseClicks(event);
			break;
		case sf::Event::MouseButtonReleased:
			break;
		case sf::Event::MouseWheelScrolled:
			const double zoomAmount{ 1.1 };
			if (event.mouseWheelScroll.delta > 0)
				_mainView.zoom(zoomAmount);
			if (event.mouseWheelScroll.delta < 0)
				_mainView.zoom(1.0/ zoomAmount);
			break;
		}
	}
}

void Game::update(sf::Time _deltaTime)
{
	updateEntities();
	mousePosition = sf::Vector2f(sf::Mouse::getPosition(*_window).x, sf::Mouse::getPosition(*_window).y);

	string printme =  "Entity Count: " + std::to_string(_entities.size()) + "\n";
	printme += "Brute Force Checks: " + std::to_string(_entities.size() * (_entities.size() - 1)) + "\n";
	printme += "Entity Spatial Checks : " + std::to_string(_CollisionSystem->collisionChecks);

	text.setString(printme);
	text.setFillColor(sf::Color::Black);

	updateStatistics(_deltaTime);

	// Set MainView center to player position
	_mainView.setCenter(GetPlayer()->_position);
}

void Game::render(LevelManager *level)
{
	// Window Clear
	_window->clear(sf::Color::White);

	// Set Window View (MainView)
	_window->setView(_mainView);

	// Render Map
	_LevelManager->renderFloor(*_window);
	//_LevelManager->renderLayer1(*_window);
	renderEntities();

	//Draw collision grid
	if (_isGridActive) 
	{
		_CollisionSystem->drawGrid();
	}

	// Set Window View (DefaultView)
	_window->setView(_window->getDefaultView());
	//Draw UI
	_window->draw(text);
	_window->draw(_FPS);

	// Window Display
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
		it->update(_deltaTime);
	}
}

void Game::renderEntities()
{
	std::sort(_entities.begin(), _entities.end(), [](const Entity* a, const Entity* b) {return a->_position.y < b->_position.y; });
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

void Game::updateStatistics(sf::Time _deltaTime)
{
	_updateTime += _deltaTime;
	_numFrames += 1;

	if (_updateTime >= sf::seconds(1.0f))
	{
		_FPS.setString("Frames / Second: " + to_string(_numFrames) +
			"Time / Update = " + to_string(_updateTime.asSeconds() / _numFrames) + " us");

		_updateTime -= sf::seconds(1.0f);
		_numFrames = 0;
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
