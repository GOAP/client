#include "SfVectorMath.h"


SfVectorMath::SfVectorMath()
{
}


SfVectorMath::~SfVectorMath()
{
}


float dotProductOf(sf::Vector2f& vector1, sf::Vector2f& vector2)
{
	return (vector1.x * vector2.x + vector1.y * vector2.y);
}

float magnitudeOf(sf::Vector2f& vector)
{
	return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
}

sf::Vector2f normalize(sf::Vector2f& vector)
{
	float magnitude = magnitudeOf(vector);
	return sf::Vector2f(vector.x / magnitude, vector.y / magnitude);
}

sf::Vector2f rotateCounterClockwise(sf::Vector2f& vector, float angle)
{
	return sf::Vector2f(vector.x * cos(angle  * 3.14 / 180) - vector.y * sin(angle * 3.14 / 180), vector.x * sin(angle * 3.14 / 180) + vector.y * cos(angle * 3.14 / 180));
}

float angleBetweenVectors(sf::Vector2f& vector1, sf::Vector2f& vector2)
{
	return (atan2(vector2.y, vector2.x) - atan2(vector1.y, vector1.x)) * 180 / 3.14;
}

float distanceBetweenPoints(sf::Vector2f& vector1, sf::Vector2f& vector2)
{
	return magnitudeOf(vector1 - vector2);
}