#pragma once
#include <SFML/Graphics.hpp>


class Agent
{
private:
	sf::Vector2f position;
	sf::Vector2f direction;

	sf::CircleShape shape;
public:
	Agent();
	Agent(int radious, float x, float y);
	~Agent();

	sf::CircleShape getShape();
	sf::Vector2f* getPositionReference();
	sf::Vector2f* getDirectionReference();

	void setPosition(sf::Vector2f& newPosition);
};

