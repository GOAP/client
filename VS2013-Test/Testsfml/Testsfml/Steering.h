#pragma once
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "StaticEntity.h"
#include "SfVectorMath.h"

class Steering
{
private:
	sf::Vector2f* agentPosition;
	sf::Vector2f* agentDirection;

	std::vector<StaticEntity> detectedPoints;
	
	int detectionRange = 50;
	
	std::vector<StaticEntity> relaventList(std::vector<StaticEntity> from, sf::Vector2f alignment);

	//Private utility method
	bool match(StaticEntity toMatch, std::vector<StaticEntity> from);

public:
	Steering();
	Steering(sf::Vector2f* sentPosition, sf::Vector2f* sentDirection);
	~Steering();

	std::vector<StaticEntity> collisionAvoidTo(sf::Vector2f* goalPosition, std::vector<StaticEntity> listOfStatics);
};

