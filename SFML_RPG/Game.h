#pragma once

#include <SFML/Graphics.hpp>

class Game 
{
public:
	Game();
	~Game();

	void Run();

private:

	void HandleInput();
	void Update();
	void Render();

private:

	sf::RenderWindow m_Window;
	sf::CircleShape m_Player;

};
