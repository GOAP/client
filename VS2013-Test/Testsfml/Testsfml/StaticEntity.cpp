#include "StaticEntity.h"

bool operator==(const StaticEntity &left, const StaticEntity &right)
{
	return left.position.x == right.position.x && left.position.y == right.position.y;
}

bool operator!=(const StaticEntity &left, const StaticEntity &right)
{
	return !(left.position.x == right.position.x && left.position.y == right.position.x);
}

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

