#include "Goblin.h"



Goblin::Goblin(sf::Vector2f position, sf::Texture* texture)
{
	constructEnemy(position, sf::Vector2f(128, 128), texture);
	initEnemyTextures();

	_name = "Goblin";
}


Goblin::~Goblin()
{
}

void Goblin::update(sf::Time _deltaTime)
{
	aiUpdate(_deltaTime);

}

void Goblin::render(sf::RenderWindow& _window)
{
	aiRender(_window);

}

void Goblin::processEvents(sf::Event& event)
{
	aiProcessEvents(event);
}

