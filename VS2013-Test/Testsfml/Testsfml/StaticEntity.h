#pragma once
#include <SFML/Graphics.hpp>
class StaticEntity
{
	friend bool StaticEntity::operator==(const StaticEntity &left, const StaticEntity &right);
	friend bool StaticEntity::operator!=(const StaticEntity &left, const StaticEntity &right);

private:
	sf::Vector2f position;
	sf::CircleShape shape;


public:
	StaticEntity(int radious, float x, float y);
	~StaticEntity();

	sf::CircleShape getShape();
	sf::Vector2f getPosition();
};

