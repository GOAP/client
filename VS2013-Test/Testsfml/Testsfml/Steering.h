#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "StaticEntity.h"
#include "SfVectorMath.h"
class Steering
{
private:
	friend void steerTo(sf::Vector2f* agentPosition, sf::Vector2f* goalPosition, std::vector<StaticEntity> listOfEntities);

public:
	Steering();
	~Steering();
};

