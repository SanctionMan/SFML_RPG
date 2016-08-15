#pragma once
#include "Enemy.h"

class Enemy;
class Goblin : public Enemy
{
public:
	Goblin(sf::Vector2f position, sf::Texture* texture);
	~Goblin();

	void update(sf::Time _deltaTime);
	void render(sf::RenderWindow &_window);
	void processEvents(sf::Event &event);

private:

};

