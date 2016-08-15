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

	std::string _name;

	sf::Vector2f _position;

	sf::RectangleShape _bounds;
	sf::CircleShape _shape;

	float _radius = 0.f;
	float _mass = 1.f;
	sf::Vector2f _adjustment_xy;
};

