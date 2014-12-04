#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <time.h>
#include <random>
#include "VS2013-Test\Testsfml\Testsfml\SfVectorMath.h"
#include "VS2013-Test\Testsfml\Testsfml\StaticEntity.h"

/*
Vector containers holding all objects.
Seperate lists for interactalbe and static objects
*/
std::vector<sf::Vector2f> staticPositions;
std::vector<StaticEntity> staticEntities;


bool isTruefalse = true;

int main(int argc, char* argv[]) {
	sf::RenderWindow App(sf::VideoMode(800, 600), "myproject");

	//Seed random number generator.
	srand(time(NULL));

	for (int i = 0; i <= 20; ++i)
	{
		staticEntities.push_back(StaticEntity(20, rand() % 600, rand() % 800, staticPositions));
	}

	while (App.isOpen()) {
		sf::Event Event;

		while (App.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				App.close();			
		}
		
		
		for (int i = 0; i <= staticEntities.size() - 1; ++i)
		{
			App.draw(staticEntities[i].getShape());
		}

		App.display();
	}
}
