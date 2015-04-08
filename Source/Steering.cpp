#include "Steering.h"

bool Steering::isNotMatch(Entity toMatch, std::vector<Entity*> from)
{
	if (from.empty())
		return true;
	for (int i = 0; i <= from.size() - 1; i++)
	{
		if (toMatch == *from[i])
			return false;
		return true;
	}
}

std::vector<Entity*> Steering::relaventList(std::vector<Entity*> from, sf::Vector2f alignment)
{
	if (from.empty())
		return from;
	else
	{
		for (int i = 0; i <= from.size() - 1 && !from.empty(); i++)
		{
			float tempAngle = angleBetweenVectors(normalize(from[i]->getPosition() - *agentPosition), normalize(alignment));
			if (tempAngle < 270 && tempAngle > 90 || distanceBetweenPoints(from[i]->getPosition(), *agentPosition) > detectionRange)
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
	detectionRange = 100;
	agentPosition = sentPosition;
	agentDirection = sentDirection;
}


Steering::~Steering()
{
}

std::vector<Entity*> Steering::collisionAvoidTo(sf::Vector2f* goalPosition, std::vector<Entity*> listOfStatics)
{
	//Normalizes alignemntVector in order to avoid a teleportation glitch.
	sf::Vector2f alignmentVector = normalize(*goalPosition - *agentPosition);

	*agentDirection = alignmentVector;

	//For loop to find all static entties in the required range.
	for (int i = 0; i <= listOfStatics.size() - 1; i++)
	{
		//isNotMatch() method ignores already added entities.
		if (distanceBetweenPoints(*agentPosition, listOfStatics[i]->getPosition()) < detectionRange && isNotMatch(*listOfStatics[i], detectedPoints))
			detectedPoints.push_back(listOfStatics[i]);
	}

	//Removes entities that are consirered irelevant from the list.(ones that are behind the AI agent).
	detectedPoints = relaventList(detectedPoints, alignmentVector);

	for (int i = 0; i <= detectedPoints.size() - 1 && !detectedPoints.empty(); i++)
	{
		//Ajusts the movement angle based on the agle between the alignemnt vector and the line between the agent and the entity.
		/*
		Simple discription:
		Smaller the angle between the two the larger the initial chang will be. 
		0 degrees will produce a 90 degree change.
		*/
		float tempAngle = signedAngleBetweenVectors(alignmentVector, normalize(detectedPoints[i]->getPosition() - *agentPosition));
		*agentDirection = rotateCounterClockwise(*agentDirection, 2 * (-90 + tempAngle / (i + 1)));
	}

	//Finalizes the agent direction to be used when moving the agent.
	*agentDirection += alignmentVector;
	*agentDirection = normalize(*agentDirection);

	//Changes the final agent position based on line formula.
	agentPosition->x += 1 * agentDirection->x;
	agentPosition->y += 1 * agentDirection->y;

	//Returns the detected points to be rendered for fizualization. 
	return detectedPoints;
}


