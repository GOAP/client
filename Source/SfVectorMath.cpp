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
	/*
	Check compensates for a drawback in the method used where to rotate more
	than 180 degrees a negative value between -180 and 0 has to be entered.
	E.g To rotate 270 degrees a value of -90 would have to be entered.
	*/
	if (angle > 180)
		angle -= 360;
	return sf::Vector2f(vector.x * cos(angle  * 3.14 / 180) - vector.y * sin(angle * 3.14 / 180), vector.x * sin(angle * 3.14 / 180) + vector.y * cos(angle * 3.14 / 180));
}

float angleBetweenVectors(sf::Vector2f& vector1, sf::Vector2f& vector2)
{
	/*
	Check compensates for a drawback in the method where the returned value would be between
	0 and +-180 degrees. 
	E.g 270 degrees: -90 degrees.
	*/
	return (atan2(vector2.y, vector2.x) - atan2(vector1.y, vector1.x)) * 180 / 3.14 >= 0 ?  (atan2(vector2.y, vector2.x) - atan2(vector1.y, vector1.x)) * 180 / 3.14 : (atan2(vector2.y, vector2.x) - atan2(vector1.y, vector1.x)) * 180 / 3.14 + 360;
}

float signedAngleBetweenVectors(sf::Vector2f& vector1, sf::Vector2f& vector2)
{
	/*
	Version o the angleBetweenVectors method that returns a value between -180 : 180.
	Returned value is positive if vector2 is couterclockwise of vector1.
	Return value is negative if vector2 is clockwise of vector1.
	*/
	return (atan2(vector2.y, vector2.x) - atan2(vector1.y, vector1.x)) * 180 / 3.14;
}

float distanceBetweenPoints(sf::Vector2f& vector1, sf::Vector2f& vector2)
{
	return magnitudeOf(vector1 - vector2);
}