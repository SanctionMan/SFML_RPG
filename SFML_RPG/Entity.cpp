#include "Entity.h"



Entity::Entity():
	_position(0,0),
	_bounds(sf::Vector2f(0,0)),
	_shape(_radius)
{

}


Entity::~Entity()
{
}

void Entity::entityEvents(sf::Event& event)
{
	switch (event.type)
	{
	case sf::Event::KeyPressed:

		break;
	}
	if (event.KeyPressed == sf::Keyboard::F4)
	{
		_drawBounds = !_drawBounds;
	}
	//if ((event.type == sf::Event::Keypressed) && (event.key.code == sf::Keyboard::F4)) dont work


}

