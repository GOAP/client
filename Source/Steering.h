#pragma once
#include <iostream>
#include <math.h>
#include <SFML/Graphics.hpp>
#include <vector>
#include "StaticEntity.h"
#include "SfVectorMath.h"
#include "Entity.h"

class Steering
{
private:
	sf::Vector2f* agentPosition;
	sf::Vector2f* agentDirection;

	std::vector<Entity*> detectedPoints;
	
	int detectionRange;
	
	std::vector<Entity*> relaventList(std::vector<Entity*> from, sf::Vector2f alignment);
	std::vector<Entity*> relaventList(std::vector<Entity*> from, sf::Vector2f alignment, Entity* toGoTo);

	//Private utility method
	bool isNotMatch(Entity toMatch, std::vector<Entity*> from);

public:
	Steering();
	Steering(sf::Vector2f* sentPosition, sf::Vector2f* sentDirection);
	~Steering();

	std::vector<Entity*> collisionAvoidTo(sf::Vector2f* goalPosition, std::vector<Entity*> listOfStatics);
	std::vector<Entity*> collisionAvoidTo(sf::Vector2f* goalPosition, std::vector<Entity*> listOfStatics, Entity* toGoTo);
};

