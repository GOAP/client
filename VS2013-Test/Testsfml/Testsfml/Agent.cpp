#include "Agent.h"


Agent::Agent(int radious, float x, float y)
{
	shape = sf::CircleShape(radious);
	position = sf::Vector2f(x, y);

	positionReference = &position;
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
	return positionReference;
}
