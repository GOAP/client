#pragma once
#include <math.h>
#include <SFML/Graphics.hpp>

class SfVectorMath
{
	
private:
	

public:
	SfVectorMath();
	~SfVectorMath();


	friend float dotProductOf(sf::Vector2f& vector1, sf::Vector2f& vector2);
	

	friend float magnitudeOf(sf::Vector2f& vector);
	

	friend sf::Vector2f normalize(sf::Vector2f& vector);
	

	friend sf::Vector2f rotateCounterClockwise(sf::Vector2f& vector, float angle);
	

	friend float angleBetweenVectors(sf::Vector2f& vector1, sf::Vector2f& vector2);
	
	friend float distanceBetweenPoints(sf::Vector2f& vector1, sf::Vector2f& vector2);
};

