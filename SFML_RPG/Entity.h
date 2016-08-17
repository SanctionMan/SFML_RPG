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

	void Entity::entityEvents(sf::Event& event);

public:

	bool _drawBounds = false;
	float _radius = 0.f;
	float _mass = 1.f;

	std::string _name;
	sf::Vector2f _position;
	sf::CircleShape _bounds;
	sf::Vector2f _adjustment_xy;
};

