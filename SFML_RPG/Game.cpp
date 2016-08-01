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
	sf::Clock clock;
	sf::Time ElapsedTime = clock.getElapsedTime();
	float FrameTime = 1.0f / 60.0f;
	while (m_Window.isOpen())
	{
		ElapsedTime += clock.restart();
		while (ElapsedTime.asSeconds() >= FrameTime)
		{
			HandleInput();
			Update(ElapsedTime);
			ElapsedTime -= sf::seconds(FrameTime);
		}
		Render();
	}
}

sf::RenderWindow* Game::GetWindow()
{
	return &m_Window;
}

void Game::HandleInput()
{
	sf::Event event;
	while (m_Window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			m_Window.close();
			break;
		}
	}
}

void Game::Update(sf::Time ElapsedTime)
{
	sf::Vector2f movement(0.f, 0.f);
	if (m_IsMovingUp)
		movement.y -= PlayerSpeed;
	if (m_IsMovingDown)
		movement.y += PlayerSpeed;
	if (m_IsMovingLeft)
		movement.x -= PlayerSpeed;
	if (m_IsMovingRight)
		movement.x += PlayerSpeed;
	m_Player.move(movement * ElapsedTime.asSeconds());
}

void Game::Render()
{
	m_Window.clear();
	m_Window.draw(m_Player);
	m_Window.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		m_IsMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		m_IsMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		m_IsMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		m_IsMovingRight = isPressed;
}
