#include "Steering.h"


Steering::Steering()
{
}


Steering::~Steering()
{
}

void steerTo(sf::Vector2f* agentPosition, sf::Vector2f* goalPosition, std::vector<StaticEntity> listOfEntities)
{
	std::vector<sf::Vector2f> detectedPoints;

	while (agentPosition->x != goalPosition->x && agentPosition->y != goalPosition->y)
	{
		for (int i = 0; i <= listOfEntities.size() - 1; ++i)
		{
			if (distanceBetweenPoints(listOfEntities[i].getPosition(), *agentPosition) < 80)
				detectedPoints.push_back(listOfEntities[i].getPosition());
		}
		sf::Vector2f agentDirection = *goalPosition - *agentPosition;
		if (detectedPoints.empty()){}
		else
		{
			for (int i = 0; i <= detectedPoints.size() - 1; ++i)
			{
				agentDirection -= detectedPoints[i];
			}
		}

		agentDirection = normalize(agentDirection);
		
		sf::sleep(sf::seconds(0.01));

		agentPosition->x += 1 * agentDirection.x;
		agentPosition->y += 1 * agentDirection.y;

		detectedPoints.clear();

	}
}
