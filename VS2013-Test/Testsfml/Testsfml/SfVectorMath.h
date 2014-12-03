#pragma once
#include <math.h>
#include <SFML/Graphics.hpp>

class SfVectorMath
{
private:
	friend float magnitudeOf(sf::Vector2f vector)
	{
		return sqrt(pow(vector.x, 2) + pow(vector.y, 2));
	}

public:
	SfVectorMath();
	~SfVectorMath();


};

