#pragma once
#include <SFML/Graphics.hpp>
class StaticEntity
{
	friend bool operator==(const StaticEntity &left, const StaticEntity &right);
	friend bool operator!=(const StaticEntity &left, const StaticEntity &right);

private:
	sf::Vector2f position;
	sf::CircleShape shape;
	
	//Used to compensate for corner drawing
	sf::Vector2f publicPosition;

public:
	StaticEntity(int radious, float x, float y);
	~StaticEntity();

	sf::CircleShape getShape();
	sf::Vector2f getPosition();
};

