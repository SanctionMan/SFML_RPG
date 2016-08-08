#pragma once

#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class Game 
{
public:
	Game();
	~Game();

	void Run();
	sf::RenderWindow* GetWindow();
private:

	void Init();
	void HandleInput();
	void Update(sf::Time ElapsedTime);
	void Render();

	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

private:

	sf::RenderWindow m_Window;

	sf::Time ElapsedTime;
	float FrameTime = 1.0f / 60.0f;

	sf::CircleShape m_Player;
	sf::Sprite m_Player2;
	sf::Texture texture;
	TextureManager TextureManager;

	bool m_IsMovingUp = false;
	bool m_IsMovingDown = false;
	bool m_IsMovingLeft = false;
	bool m_IsMovingRight = false;

	float PlayerSpeed = 100;
};
