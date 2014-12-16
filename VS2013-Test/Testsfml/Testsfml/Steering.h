#pragma once
#include <iostream>
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

	bool match(StaticEntity toMatch, std::vector<StaticEntity> from);
	
	std::vector<StaticEntity> relaventList(std::vector<StaticEntity> from, sf::Vector2f alignment);


public:
	Steering();
	Steering(sf::Vector2f* sentPosition, sf::Vector2f* sentDirection);
	~Steering();

	//NewVersion
	std::vector<StaticEntity> avoid(sf::Vector2f* goalPosition, std::vector<StaticEntity> listOfStatics);

	std::vector<StaticEntity> steerTo(sf::Vector2f* goalPosition, std::vector<StaticEntity> listOfStatics);
};

