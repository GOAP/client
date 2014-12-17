#include "Steering.h"

bool Steering::match(StaticEntity toMatch, std::vector<StaticEntity> from)
{
	if (from.empty())
		return true;
	for (int i = 0; i <= from.size() - 1; i++)
	{
		if (toMatch == from[i])
			return false;
		return true;
	}
}

std::vector<StaticEntity> Steering::relaventList(std::vector<StaticEntity> from, sf::Vector2f alignment)
{
	if (from.empty())
		return from;
	else
	{
		for (int i = 0; i <= from.size() - 1 && !from.empty(); i++)
		{
			float tempAngle = angleBetweenVectors(normalize(from[i].getPosition() - *agentPosition), normalize(alignment));
			if (tempAngle < 270 && tempAngle > 90 || distanceBetweenPoints(from[i].getPosition(), *agentPosition) > detectionRange + detectionRange/2)
			{
				from.erase(from.begin() + i);
			}
		}
		return from;
	}
}


Steering::Steering(){}
Steering::Steering(sf::Vector2f* sentPosition, sf::Vector2f* sentDirection)
{
	agentPosition = sentPosition;
	agentDirection = sentDirection;
}


Steering::~Steering()
{
}

std::vector<StaticEntity> Steering::avoid(sf::Vector2f* goalPosition, std::vector<StaticEntity> listOfStatics)
{
	sf::Vector2f alignmentVector = normalize(*goalPosition - *agentPosition);
	
	for (int i = 0; i <= listOfStatics.size() - 1; i++)
	{
		if (distanceBetweenPoints(*agentPosition, listOfStatics[i].getPosition()) < detectionRange && match(listOfStatics[i], detectedPoints))
			detectedPoints.push_back(listOfStatics[i]);
	}

	//Gets rid of duplicates.
	detectedPoints.erase(std::unique(detectedPoints.begin(), detectedPoints.end()), detectedPoints.end());

	detectedPoints = relaventList(detectedPoints, alignmentVector);

	for (int i = 0; i <= detectedPoints.size() - 1 && !detectedPoints.empty(); i++)
	{
		float tempDistance = distanceBetweenPoints(*agentPosition, detectedPoints[i].getPosition());
		sf::Vector2f objectDirection = rotateCounterClockwise(normalize(detectedPoints[i].getPosition()), -tan(detectionRange/tempDistance));
		*agentDirection -= normalize(objectDirection);
	}

	*agentDirection += alignmentVector;
	*agentDirection += *agentDirection;
	*agentDirection = normalize(*agentDirection);
	
	//Movement Propper
	agentPosition->x += 1 * agentDirection->x;
	agentPosition->y += 1 * agentDirection->y;

	//detectedPoints.clear();

	return detectedPoints;
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
