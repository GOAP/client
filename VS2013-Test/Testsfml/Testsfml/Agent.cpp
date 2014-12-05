#include "Agent.h"

/*
Constructor
*/
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
	/*
	CircleShape::setPosition() is used in Agent::getShape()
	to give the impression of movement by altering the position based
	on imput from the Steering::steerTo() method.
	*/
	shape.setPosition(position);
	return shape;
}

sf::Vector2f* Agent::getPositionReference()
{
	/*
	Returns a reference to the Vector2f position variable to be used in
	the Steering::steerTo() method.
	*/
	return &position;
}
