#pragma once
#include <SFML/Graphics.hpp>

class Agent
{
private:
	sf::Vector2f position;
	sf::Vector2f* positionReference;

	sf::CircleShape shape;
public:
	Agent(int radious, float x, float y);
	~Agent();

	sf::CircleShape getShape();
	sf::Vector2f* getPositionReference();
};

