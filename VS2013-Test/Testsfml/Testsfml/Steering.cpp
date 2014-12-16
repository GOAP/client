#include "Steering.h"

Steering::Steering(){}
Steering::Steering(sf::Vector2f* sentPosition, sf::Vector2f* sentDirection)
{
	agentPosition = sentPosition;
	agentDirection = sentDirection;
}


Steering::~Steering()
{
}

std::vector<StaticEntity> Steering::steerTo(sf::Vector2f* goalPosition, std::vector<StaticEntity> listOfStatics)
{

	//Detects obsticles around the AI
	for (int i = 0; i <= listOfStatics.size() - 1; ++i)
	{
		if (distanceBetweenPoints(listOfStatics[i].getPosition(), *agentPosition) <= detectionRange)
			detectedPoints.push_back(listOfStatics[i]);
	}

	/*
	Gets the direction vector from the agent to the final goal.
	*/
	*agentDirection += normalize(*goalPosition - *agentPosition);

	if (detectedPoints.empty()){}
		else
	{
		for (int i = 0; i <= detectedPoints.size() - 1; ++i)
		{
			//float tempDistance = distanceBetweenPoints(*agentPosition, detectedPoints[i].getPosition());
			//sf::Vector2f objectDirection = rotateCounterClockwise(normalize(detectedPoints[i].getPosition()), tan(tempDistance/detectionRange));
			*agentDirection -= normalize(detectedPoints[i].getPosition());// objectDirection;
		}
	}

	if (angleBetweenVectors(*agentDirection, normalize(*goalPosition - *agentPosition)) > 90 && angleBetweenVectors(*agentDirection, normalize(*goalPosition - *agentPosition)) <= 180)
	{
		rotateCounterClockwise(*agentDirection, angleBetweenVectors(normalize(*goalPosition - *agentPosition), *agentDirection) - 90);
	}
	else if (angleBetweenVectors(*agentDirection, normalize(*goalPosition - *agentPosition)) >= 180 && angleBetweenVectors(*agentDirection, normalize(*goalPosition - *agentPosition)) < 270)
	{
		rotateCounterClockwise(*agentDirection, angleBetweenVectors(normalize(*goalPosition - *agentPosition), *agentDirection) + 90);
	}
	*agentDirection = normalize(*agentDirection);

	agentPosition->x += 1 * agentDirection->x;
	agentPosition->y += 1 * agentDirection->y;
	
	detectedPoints.clear();
	
	return detectedPoints;
}
