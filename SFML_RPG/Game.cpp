#include "Game.h"

Game::Game()
	: m_Window(sf::VideoMode(640, 480), "SFML_RPG"),
	m_Player()
{
	m_Player.setRadius(40.f);
	m_Player.setPosition(50.f, 50.f);
	m_Player.setFillColor(sf::Color::Cyan);
}

Game::~Game()
{
}

void Game::Run()
{
	while (m_Window.isOpen())
	{
		HandleInput();
		Update();
		Render();
	}
}

void Game::HandleInput()
{
	sf::Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_Window.close();
	}
}

void Game::Update()
{
}

void Game::Render()
{
	m_Window.clear();
	m_Window.draw(m_Player);
	m_Window.display();
}
