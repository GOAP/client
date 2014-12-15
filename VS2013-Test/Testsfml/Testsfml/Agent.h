#pragma once
#include <SFML/Graphics.hpp>
#include "Steering.h"

/*
Headder file for the class describing the AI agent.

Private:
Vector2f position;
Stores the x and y position of the agent.

CircleShape shape;
Stores the shape of the agent.

Public:

CircleShape getShape();
Used in the main loop for the RenderWindow::draw() method. Returns the shape from the
private section of the class

getPositionReference();
Used to parse the position to the Steering::steerTo() method. Allows the actuall
values to be altered,
*/

class Agent
{
private:
	sf::Vector2f position;
	sf::Vector2f direction;
	sf::RectangleShape directionVector;
	sf::CircleShape shape;

	

public:
	Agent(int radious, float x, float y, float r, float g, float b);
	~Agent();

	Steering steerAi;

	sf::CircleShape* getShape();
	sf::RectangleShape* getDirectionShape();
	sf::Vector2f* getPositionReference();
	sf::Vector2f* getDirectionReference();
};

