#include "Steering.h"


Steering::Steering()
{
}


Steering::~Steering()
{
}

void steerTo(sf::Vector2f* agentPosition, sf::Vector2f* goalPosition, std::vector<StaticEntity> listOfEntities)
{
	/*
	Vector container to hold coordinates of objects within the "detection range".
	*/
	std::vector<sf::Vector2f> detectedPoints;
	
	/*
	While loop runs untill the agent reaaches its final coordinates.
	*/
	while (agentPosition->x != goalPosition->x && agentPosition->y != goalPosition->y)
	{
		for (int i = 0; i <= listOfEntities.size() - 1; ++i)
		{
			/*
			Stores the position of each object within the 80 "detection range" in the 'detected points' container.
			*/
			if (distanceBetweenPoints(listOfEntities[i].getPosition(), *agentPosition) < 80)
				detectedPoints.push_back(listOfEntities[i].getPosition());
		}
		/*
		Gets the direction vector from the agent to the final goal.
		*/
		sf::Vector2f agentDirection = *goalPosition - *agentPosition;

		/*
		Calculates the actuall movement direction vector based on the list
		of detected points.
		*/
		if (detectedPoints.empty()){}
		else
		{
			for (int i = 0; i <= detectedPoints.size() - 1; ++i)
			{
				agentDirection -= detectedPoints[i];
			}
		}

		/*
		Normalizes the final vector to avoid a bug where the AI teleports to the end point.
		*/
		if (angleBetweenVectors(*goalPosition - *agentPosition, agentDirection) > 90 && angleBetweenVectors(*goalPosition - *agentPosition, agentDirection) <= 180)
		{
			rotateCounterClockwise(agentDirection, angleBetweenVectors(*goalPosition - *agentPosition, agentDirection) - 90);
		}
		else if (angleBetweenVectors(*goalPosition - *agentPosition, agentDirection) >= 180 && angleBetweenVectors(*goalPosition - *agentPosition, agentDirection) < 270)
		{
			rotateCounterClockwise(agentDirection, angleBetweenVectors(*goalPosition - *agentPosition, agentDirection) - 90);
		}
		agentDirection = normalize(agentDirection);
		
		/*
		Because of the speed this thread runs its full operation and gets to the
		goal very quickly. This causes a teleportation like effect. 
		To counter this on each iteration of the while loop the thread is put to sleep/paused for 0.01 secconds.
		*/
		sf::sleep(sf::seconds(0.01));

		/*
		Changes the agent x and y coordinates based on the general formula describing a ray.
		*/
		agentPosition->x += 1 * agentDirection.x;
		agentPosition->y += 1 * agentDirection.y;

		/*
		Clears the detectedPoints container getting it ready for the next iteration making sure 
		objects that are now far away are not going to be affecting the agent.
		*/
		detectedPoints.clear();

	}
}
