#include "Steering.h"


Steering::Steering()
{
}


Steering::~Steering()
{
}

std::vector<StaticEntity> steerTo(Agent &agentToMove, sf::Vector2f* goalPosition, std::vector<StaticEntity> listOfEntities)
{
	/*
	Vector container to hold coordinates of objects within the "detection range".
	*/
	std::vector<StaticEntity> detectedPoints;
	
	
	for (int i = 0; i <= listOfEntities.size() - 1; ++i)
	{
		/*
		Stores the position of each object within the 80 "detection range" in the 'detected points' container.
		*/
		if (distanceBetweenPoints(listOfEntities[i].getPosition(), *agentToMove.getPositionReference()) < 40)
			detectedPoints.push_back(listOfEntities[i]);
	}
	/*
	Gets the direction vector from the agent to the final goal.
	*/
	sf::Vector2f agentDirection = *goalPosition - *agentToMove.getPositionReference();

	/*
	Calculates the actuall movement direction vector based on the list
	of detected points.
	*/
	if (detectedPoints.empty()){}
	else
	{
		for (int i = 0; i <= detectedPoints.size() - 1; ++i)
		{
			agentDirection -= detectedPoints[i].getPosition();
			
			
		}
	}


	/*
	Normalizes the final vector to avoid a bug where the AI teleports to the end point.
	*/
	if (angleBetweenVectors(*goalPosition - *agentToMove.getPositionReference(), agentDirection) > 90 && angleBetweenVectors(*goalPosition - *agentToMove.getPositionReference(), agentDirection) <= 180)
	{
		rotateCounterClockwise(agentDirection, angleBetweenVectors(*goalPosition - *agentToMove.getPositionReference(), agentDirection) - 90);
	}
	else if (angleBetweenVectors(*goalPosition - *agentToMove.getPositionReference(), agentDirection) >= 180 && angleBetweenVectors(*goalPosition - *agentToMove.getPositionReference(), agentDirection) < 270)
	{
		rotateCounterClockwise(agentDirection, angleBetweenVectors(*goalPosition - *agentToMove.getPositionReference(), agentDirection) + 90);
	}
	agentDirection = normalize(agentDirection);
	
	/*
	Because of the speed this thread runs its full operation and gets to the
	goal very quickly. This causes a teleportation like effect. 
	To counter this on each iteration of the while loop the thread is put to sleep/paused for 0.01 secconds.
	*/
	//sf::sleep(sf::seconds(0.01));
	/*
	Changes the agent x and y coordinates based on the general formula describing a ray.
	*/
	agentToMove.getPositionReference()->x += 1 * agentDirection.x;
	agentToMove.getPositionReference()->y += 1 * agentDirection.y;
	
	/*
	Direction vector rotation and position.
	*/
	agentToMove.getDirectionShape()->rotate(angleBetweenVectors(*agentToMove.getDirectionReference(), agentDirection));
	agentToMove.getDirectionShape()->setPosition(sf::Vector2f(agentToMove.getPositionReference()->x, agentToMove.getPositionReference()->y));

	agentToMove.getDirectionReference()->x = agentDirection.x;
	agentToMove.getDirectionReference()->y = agentDirection.y;
	
	/*
	End of direction vector rotation and position.
	*/

	
	return detectedPoints;

}
