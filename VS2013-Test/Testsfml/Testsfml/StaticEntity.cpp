#include "StaticEntity.h"


StaticEntity::StaticEntity(int radious, float x, float y, std::vector<sf::Vector2f>& staticContainer)
{
	staticContainer.push_back(sf::Vector2f(x, y));

	position.x = x;
	position.y = y;

	shape = sf::CircleShape(radious);
}


StaticEntity::~StaticEntity()
{
}

sf::CircleShape StaticEntity::getShape()
{
	return shape;
}
