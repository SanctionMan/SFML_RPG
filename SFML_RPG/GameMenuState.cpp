#include "GameMenuState.h"



GameMenuState::GameMenuState(Game* game)
{
	this->_game = game;
	sf::Vector2f windowSize = sf::Vector2f(this->_game->_window->getSize());
	this->_view.setSize(windowSize);
	windowSize *= 0.5f;
	this->_view.setCenter(windowSize);
}


GameMenuState::~GameMenuState()
{
}

void GameMenuState::handleInput()
{
	sf::Event event;

	while (this->_game->_window->pollEvent(event))
	{
		switch (event.type)
		{
			/* Close the window */
			case sf::Event::Closed:
			{
				_game->_window->close();
				break;
			}
			/* Resize the window */
			case sf::Event::Resized:
			{
				this->_view.setSize(event.size.width, event.size.height);
				this->_game->_background.setPosition(this->_game->_window->mapPixelToCoords(sf::Vector2i(0, 0)));
				this->_game->_background.setScale(
					float(event.size.width) / float(this->_game->_background.getTexture()->getSize().x),
					float(event.size.height) / float(this->_game->_background.getTexture()->getSize().y));
				break;
			}
			case sf::Event::KeyPressed:
			{
				if (event.key.code == sf::Keyboard::Escape) this->_game->_window->close();
				else if (event.key.code == sf::Keyboard::Space) 
					this->loadGame();
					cout << "WTF" << endl;
				break;
			}
			default: break;
		}
		return;
	}
}

void GameMenuState::update(sf::Time deltaTime)
{

}

void GameMenuState::render(sf::Time deltaTime)
{
	this->_game->_window->setView(this->_view);
	this->_game->_window->clear(sf::Color::Black);

	this->_game->_window->draw(_game->_background);


	this->_game->_window->display();
	return;
}

void GameMenuState::loadGame()
{
	this->_game->pushState(new GamePlayState(this->_game));
	return;
}



