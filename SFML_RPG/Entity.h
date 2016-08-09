#pragma once
#include "SFML\Graphics.hpp"

class Entity
{
public:
	Entity();
	~Entity();

	virtual void update(sf::Time _deltaTime) = 0;
	virtual void render(sf::RenderWindow &_window) = 0;
	virtual void processEvents(sf::Event &event) = 0;

	sf::Vector2f _position;
	std::string _name;

};

