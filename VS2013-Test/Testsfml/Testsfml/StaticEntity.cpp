#include "StaticEntity.h"


StaticEntity::StaticEntity(int radious, float x, float y)
{
	position.x = x;
	position.y = y;

	shape = sf::CircleShape(radious);
}


StaticEntity::~StaticEntity()
{
}

sf::CircleShape StaticEntity::getShape()
{
	shape.setPosition(position);
	return shape;
}

sf::Vector2f StaticEntity::getPosition()
{
	return position;
}

