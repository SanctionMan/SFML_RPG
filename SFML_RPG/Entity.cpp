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
