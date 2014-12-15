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
		if (distanceBetweenPoints(listOfStatics[i].getPosition(), *agentPosition) <= 40)
			detectedPoints.push_back(listOfStatics[i]);
	}

	/*
	Gets the direction vector from the agent to the final goal.
	*/
	*agentDirection = normalize(*goalPosition - *agentPosition);

	/*
	Irelavent List
	*/
	if (Steering::detectedPoints.empty()){}
	else
	{
		for (int i = 0; i <= detectedPoints.size() - 1; ++i)
		{
			float tempAngle = angleBetweenVectors(normalize(*goalPosition - *agentPosition), normalize(detectedPoints[i].getPosition() - *agentPosition));
			if (tempAngle >= 90 && tempAngle <= 270)
				detectedPoints.erase(detectedPoints.begin() + i);
		}
	}
		

	if (Steering::detectedPoints.empty()){}
		else
	{
		for (int i = 0; i <= Steering::detectedPoints.size() - 1; ++i)
		{
			*agentDirection -= normalize(Steering::detectedPoints[i].getPosition());
			
		}
	}

	if (angleBetweenVectors(normalize(*goalPosition - *agentPosition), *agentDirection) > 90 && angleBetweenVectors(normalize(*goalPosition - *agentPosition), *agentDirection) <= 180)
	{
		rotateCounterClockwise(*agentDirection, angleBetweenVectors(normalize(*goalPosition - *agentPosition), *agentDirection) - 95);
	}
	else if (angleBetweenVectors(normalize(*goalPosition - *agentPosition), *agentDirection) > 180 && angleBetweenVectors(normalize(*goalPosition - *agentPosition), *agentDirection) <= 270)
	{
		rotateCounterClockwise(*agentDirection, angleBetweenVectors(normalize(*goalPosition - *agentPosition), *agentDirection) + 95);
	}
	*agentDirection = normalize(*agentDirection);

	agentPosition->x += 1 * agentDirection->x;
	agentPosition->y += 1 * agentDirection->y;
	
	detectedPoints.clear();
	
	return detectedPoints;
}

//std::vector<StaticEntity> steerTo(Agent &agentToMove, sf::Vector2f* goalPosition, std::vector<StaticEntity> listOfEntities)
//{
//	/*
//	Vector container to hold coordinates of objects within the "detection range".
//	*/
//	
//	sf::Vector2f agentDirection = *agentToMove.getDirectionReference();
//	
//	for (int i = 0; i <= listOfEntities.size() - 1; ++i)
//	{
//		/*
//		Stores the position of each object within the 80 "detection range" in the 'detected points' container.
//		*/
//		if (distanceBetweenPoints(listOfEntities[i].getPosition(), *agentToMove.getPositionReference()) < 80)
//			Steering::detectedPoints.push_back(listOfEntities[i]);
//	}
//
//	
//
//	/*
//	Gets the direction vector from the agent to the final goal.
//	*/
//	agentDirection = normalize(*goalPosition - *agentToMove.getPositionReference());
//	agentDirection = normalize(agentDirection);
//
//	for (int i = 0; i <= Steering::detectedPoints.size() - 1; ++i)
//	{
//		if (Steering::detectedPoints[i])
//	}
//
//	/*
//	Calculates the actuall movement direction vector based on the list
//	of detected points.
//	*/
//	if (Steering::detectedPoints.empty()){}
//	else
//	{
//		for (int i = 0; i <= Steering::detectedPoints.size() - 1; ++i)
//		{
//			agentDirection -= normalize(Steering::detectedPoints[i].getPosition());
//			
//		}
//	}
//
//
//	/*
//	Normalizes the final vector to avoid a bug where the AI teleports to the end point.
//	*/
//	if (angleBetweenVectors(normalize(*goalPosition - *agentToMove.getPositionReference()), agentDirection) > 90 && angleBetweenVectors(normalize(*goalPosition - *agentToMove.getPositionReference()), agentDirection) <= 180)
//	{
//		rotateCounterClockwise(agentDirection, angleBetweenVectors(normalize(*goalPosition - *agentToMove.getPositionReference()), agentDirection) - 85);
//	}
//	else if (angleBetweenVectors(normalize(*goalPosition - *agentToMove.getPositionReference()), agentDirection) > 180 && angleBetweenVectors(normalize(*goalPosition - *agentToMove.getPositionReference()), agentDirection) <= 270)
//	{
//		rotateCounterClockwise(agentDirection, angleBetweenVectors(normalize(*goalPosition - *agentToMove.getPositionReference()), agentDirection) + 85);
//	}
//	agentDirection = normalize(agentDirection);
//	
//	/*
//	Because of the speed this thread runs its full operation and gets to the
//	goal very quickly. This causes a teleportation like effect. 
//	To counter this on each iteration of the while loop the thread is put to sleep/paused for 0.01 secconds.
//	*/
//	//sf::sleep(sf::seconds(0.01));
//	/*
//	Changes the agent x and y coordinates based on the general formula describing a ray.
//	*/
//	agentToMove.getPositionReference()->x += 1 * agentDirection.x;
//	agentToMove.getPositionReference()->y += 1 * agentDirection.y;
//	
//	/*
//	Direction vector rotation and position.
//	*/
//	agentToMove.getDirectionShape()->rotate(angleBetweenVectors(*agentToMove.getDirectionReference(), agentDirection));
//	agentToMove.getDirectionShape()->setPosition(sf::Vector2f(agentToMove.getPositionReference()->x, agentToMove.getPositionReference()->y));
//
//	agentToMove.getDirectionReference()->x = agentDirection.x;
//	agentToMove.getDirectionReference()->y = agentDirection.y;
//	
//
//	/*
//	Returns for the list of detected obsticles for visualization
//	*/
//	return Steering::detectedPoints;
//
//}
