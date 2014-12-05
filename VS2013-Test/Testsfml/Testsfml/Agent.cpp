#include "Agent.h"


Agent::Agent(int radious, float x, float y)
{
	shape = sf::CircleShape(radious);
	position = sf::Vector2f(x, y);
}


Agent::~Agent()
{
}

sf::CircleShape Agent::getShape()
{
	shape.setPosition(position);
	return shape;
}

sf::Vector2f* Agent::getPositionReference()
{
	return &position;
}

sf::Vector2f* Agent::getDirectionReference()
{
	return &direction;
}

void Agent::setPosition(sf::Vector2f& newPosition)
{
	position.x = newPosition.x;
	position.y = newPosition.y;
}