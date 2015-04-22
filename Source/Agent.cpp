#include "Agent.h"

/*
Constructor
*/
Agent::Agent(int radious, float x, float y, float r, float g, float b)
{
	/*
	AI Triangle.
	*/
	shape = sf::CircleShape(radious, 3);
	shape.setFillColor(sf::Color(r, g, b));
	
	/*
	AI Direction Vector.
	*/
	directionVector = sf::RectangleShape(sf::Vector2f(20, 3));
	directionVector.setFillColor(sf::Color(0, 0, 240));

	position = sf::Vector2f(x, y);
	direction = sf::Vector2f(0, 0);

	steerAi = Steering(&position, &direction);
}


Agent::~Agent()
{
}

sf::CircleShape* Agent::getShape()
{
	/*
	CircleShape::setPosition() is used in Agent::getShape()
	to give the impression of movement by altering the position based
	on imput from the Steering::steerTo() method.
	*/
	shape.setPosition(position);
	return &shape;
}
sf::RectangleShape* Agent::getDirectionShape()
{
	
	directionVector.setRotation(-angleBetweenVectors(direction, sf::Vector2f(1, 0)));
	directionVector.setPosition(position);
	return &directionVector;
}

sf::Vector2f* Agent::getPositionReference()
{
	/*
	Returns a reference to the Vector2f position variable to be used in
	the Steering::steerTo() method.
	*/
	return &position;
}

sf::Vector2f* Agent::getDirectionReference()
{
	/*
	Returns a reference to the Vector2f direction variable to be used in
	the Steering::steerTo() method.
	*/
	return &direction;
}

