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
*/
class SfVectorMath
{
public:
	SfVectorMath();
	~SfVectorMath();

	/*===============================Methods==================================*/
	/*
	Returns a float which is the scalar(dot product) of the two vectors parsed
	in the arguments.
	*/
	friend float dotProductOf(sf::Vector2f& vector1, sf::Vector2f& vector2);
	
	/*
	Returns a float which is the lenght(magnitude) of the given vector.
	*/
	friend float magnitudeOf(sf::Vector2f& vector);
	
	/*
	Returns a vector2f which is derived by normalizing(converting to unit vectror) the 
	given vector.
	The output of this metod has the same "direction" as the original vector but
	a magnitude of '1'.
	*/
	friend sf::Vector2f normalize(sf::Vector2f& vector);

	/*
	Returns a vector which is rotated counter clockwise.
	*/
	friend sf::Vector2f rotateCounterClockwise(sf::Vector2f& vector, float angle);

	/*
	Returns the angle beween the vectors. Returned value is a signed float between +- 180. 
	If it is positive that means the second vector is in the clockwise direction.
	If it is negative that means the second vector is in the anti cockwise direction.
	*/
	friend float angleBetweenVectors(sf::Vector2f& vector1, sf::Vector2f& vector2);
	
	/*
	Returns the distance between two points descrbed by the two vectors.
	*/
	friend float distanceBetweenPoints(sf::Vector2f& vector1, sf::Vector2f& vector2);
};

