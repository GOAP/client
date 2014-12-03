#pragma once
#include <math.h>
#include <SFML/Graphics.hpp>

class SfVectorMath
{
private:

	friend float dotProductOf(sf::Vector2f& vector1, sf::Vector2f& vector2)
	{
		return vector1.x * vector2.x + vector1.y * vector2.y;
	}

	friend float magnitudeOf(sf::Vector2f& vector)
	{
		return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	}

	friend sf::Vector2f normalize(sf::Vector2f& vector)
	{
		float magnitude = magnitudeOf(vector);
		return sf::Vector2f(vector.x / magnitude, vectr.y / magnitude);
	}

	friend sf::Vector2f rotateCounterClockwise(sf::Vector2f& vector, float angle)
	{
		return sf::Vector2f(vector.x * cos(angle) - vector.y * sin(angle), vector.x * sin(angle) + vector.y * cos(angle));
	}

	friend float angleBetweenVectors(sf::Vector2f& vector1, sf::Vector2f& vector2)
	{
		return acos(dotProductOf(vector1, vector2));
	}
 

public:
	SfVectorMath();
	~SfVectorMath();


};

