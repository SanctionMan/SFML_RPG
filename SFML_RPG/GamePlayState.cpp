#include "GamePlayState.h"



GamePlayState::GamePlayState(Game* game)
{
	this->_game = game;
	sf::Vector2f windowSize = sf::Vector2f(this->_game->_window->getSize());
	this->_view.setSize(windowSize);
	windowSize *= 0.5f;
	this->_view.setCenter(windowSize);
}


GamePlayState::~GamePlayState()
{
}

void GamePlayState::handleInput()
{
	sf::Event event;

	while (this->_game->_window->pollEvent(event))
	{
		switch (event.type)
		{
			/* Close the window */
		case sf::Event::Closed:
			_game->_window->close();
			break;
		/* Resize the window */
		case sf::Event::Resized:
			//this->_view.setSize(event.size.width, event.size.height);
			//this->_game->_background->setPosition(this->_game->_window->mapPixelToCoords(sf::Vector2i(0, 0)));
			//this->_game->_background->setScale(
			//	float(event.size.width) / float(this->_game->_background->getTexture()->getSize().x),
			//	float(event.size.height) / float(this->_game->_background->getTexture()->getSize().y));
			break;
		case sf::Event::KeyPressed:
			this->_game->processEntities(event);
			if (event.key.code == sf::Keyboard::Escape) this->_game->_window->close();
			if (event.key.code == sf::Keyboard::F3) this->_game->_isGridActive = !this->_game->_isGridActive;
			break;
		case sf::Event::KeyReleased:
			this->_game->processEntities(event);
			break;
		case sf::Event::MouseButtonPressed:
			this->_game->mouseClicks(event);
			break;
		case sf::Event::MouseButtonReleased:
			break;
		case sf::Event::MouseWheelScrolled:
			const double zoomAmount{ 1.1 };
			if (event.mouseWheelScroll.delta > 0)
				_view.zoom(zoomAmount);
			if (event.mouseWheelScroll.delta < 0)
				_view.zoom(1.0 / zoomAmount);
			break;
		}
		return;
	}
}

void GamePlayState::update(sf::Time deltaTime)
{
	this->_game->updateEntities();
	this->_game->_CollisionSystem->update(this->_game->_entities);
	this->_game->_LevelManager->update(deltaTime);
	this->_view.setCenter(GetPlayer()->_position);
	cout << "updating" << endl;
}

void GamePlayState::render(sf::Time deltaTime)
{
	this->_game->_window->setView(this->_view);
	this->_game->_window->clear(sf::Color::Black);

	this->_game->_LevelManager->renderFloor(*this->_game->_window);
	this->_game->renderEntities();

	this->_game->_window->display();
	return;
}
