#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include "StaticEntity.h"
#include "SfVectorMath.h"
#include "Agent.h"

class Steering
{
private:
	friend std::vector<StaticEntity> steerTo(Agent &agentToMove, sf::Vector2f* goalPosition, std::vector<StaticEntity> listOfEntities);

public:
	Steering();
	~Steering();
};

