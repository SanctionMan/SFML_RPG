#pragma once

#include "SFML/Graphics.hpp"

class HealthBar
{
public:
	HealthBar();
	~HealthBar();

	void update(sf::Time _deltaTime);
	void render(sf::RenderWindow &_window);

	void setPosition(sf::Vector2f position);
	void setPosition(float x, float y);
	void setCurrentHealth(float &health);
	void setCurrentMana(float &mana);
	void setMaxHealth(float &maxHealth);
	void setMaxMana(float &maxMana);
	void setAdjustment(sf::Vector2f adjustment);

private:

	sf::Vector2f _size;
	sf::Vector2f _backgroundAdjustment;
	sf::Vector2f _healthAdjustment;
	sf::Vector2f _manaAdjustment;


	float _maxHealth = 100;
	float _maxMana = 100;
	float _currentHealth = 100;
	float _currentMana = 100;

	sf::Vector2f _position;
	sf::RectangleShape _background;
	sf::RectangleShape _healthBar;
	sf::RectangleShape _manaBar;

};

