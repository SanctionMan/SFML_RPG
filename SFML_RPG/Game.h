#pragma once

#include <SFML/Graphics.hpp>

class Game 
{
public:
	Game();
	~Game();

	void Run();
	sf::RenderWindow* GetWindow();
private:

	void HandleInput();
	void Update(sf::Time ElapsedTime);
	void Render();

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:

	sf::RenderWindow m_Window;
	sf::CircleShape m_Player;

	bool m_IsMovingUp;
	bool m_IsMovingDown;
	bool m_IsMovingLeft;
	bool m_IsMovingRight;

	float PlayerSpeed = 100;
};
