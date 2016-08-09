#include "Game.h"

Game::Game()
	: _window(sf::VideoMode(640, 480), "SFML_RPG")
{

}

Game::~Game()
{
}

void Game::Run()
{
	//Manager Setup:
	init();

	sf::Clock clock;
	_elapsedTime = clock.getElapsedTime();
	while (_window.isOpen())
	{
		_elapsedTime += clock.restart();
		while (_elapsedTime.asSeconds() >= _frameTime)
		{
			handleInput();
			update(_elapsedTime);
			_elapsedTime -= sf::seconds(_frameTime);
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
	//Load Textures 
	TextureManager.loadTexture("Mushroom.png", "Resources/Textures/Mushroom.png");

	//Show Textures that are loaded into memory
	TextureManager.showTexturesList();

	//Create Player and Set Texture
	createEntity(new Player(TextureManager.getTexture("Mushroom.png"), sf::Vector2f(100,100)));
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
	_window.clear(sf::Color::Magenta);
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
