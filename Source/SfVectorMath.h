#pragma once
/*
math.h library used for:

sqrt - magnitudeOf();
sin - rotateCounterClockwise()
cos - rotateCounterClockwise()
atan2 - angleBetweenVectors();
pow - magnitudeOf();
*/
#include <math.h> 
#include <SFML/Graphics.hpp>


/*
This headder describes a class of friend methods implementing
basic 2D vector operations using the 'sf::Vector2f' data type.

Constructors are not used and an instance of the class does not
need to be created for the methods to be implemented.

float dotProductOf(Vector2f vector1, Vector2f vector2);
Returns a number describing the dot product of the two Vector2f arguments.

float magnitudeOf(Vector2f vector);
Returns a number describing the lenght/magnitude of the Vector2f entered in the arguments.

Vector2f normalize(Vector2f vector);
Returns a Vector2f with the same direction as the Vector2f entered in the arguments but with 
a magnitude of 1.

Vector2f rotateCounterClockwise(Vector2f vector, float angle);
Returns a Vector2f which is a rotated version of the Vector2f argument by the angle.
NB: This rotation is done relative to (0,0).

float angleBetweenVectors(Vector2f vector1, Vector2f vector2);
Returns a float describing the angle between the two Vector2f arguments.
NB: The answer is relative to the 'vector1' argument!
	E.g vector1(1,0); vector2(0,-1); return is 270 degrees.
		vector1(0,-1); vector2(1,0); return is 90 degrees.

float distanceBetweenPoints(Vector2f vector1, Vector2f vector2);
Returns a float describing the distance between the two vectors/points.
*/
float dotProductOf(sf::Vector2f& vector1, sf::Vector2f& vector2);

float magnitudeOf(sf::Vector2f vector);

sf::Vector2f normalize(sf::Vector2f vector);

sf::Vector2f rotateCounterClockwise(sf::Vector2f vector, float angle);

float signedAngleBetweenVectors(sf::Vector2f vector1, sf::Vector2f vector2);

float angleBetweenVectors(sf::Vector2f vector1, sf::Vector2f vector2);

float distanceBetweenPoints(sf::Vector2f vector1, sf::Vector2f vector2);

sf::Vector2f scalarMult(float num, sf::Vector2f vec);