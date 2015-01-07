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

std::vector<StaticEntity> Steering::collisionAvoidTo(sf::Vector2f* goalPosition, std::vector<StaticEntity> listOfStatics)
{
	//Converts alignmentVeco
	sf::Vector2f alignmentVector = normalize(*goalPosition - *agentPosition);

	*agentDirection = alignmentVector;

	for (int i = 0; i <= listOfStatics.size() - 1; i++)
	{
		if (distanceBetweenPoints(*agentPosition, listOfStatics[i].getPosition()) < detectionRange && match(listOfStatics[i], detectedPoints))
			detectedPoints.push_back(listOfStatics[i]);
	}

	detectedPoints = relaventList(detectedPoints, alignmentVector);

	for (int i = 0; i <= detectedPoints.size() - 1 && !detectedPoints.empty(); i++)
	{
		float tempAngle = signedAngleBetweenVectors(alignmentVector, normalize(detectedPoints[i].getPosition() - *agentPosition));
		*agentDirection = rotateCounterClockwise(*agentDirection, 2 * (-90+tempAngle));
	}

	*agentDirection += alignmentVector;
	*agentDirection = normalize(*agentDirection);

	agentPosition->x += 1 * agentDirection->x;
	agentPosition->y += 1 * agentDirection->y;

	return detectedPoints;
}


