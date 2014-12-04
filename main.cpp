#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "VS2013-Test\Testsfml\Testsfml\SfVectorMath.h"
#include "VS2013-Test\Testsfml\Testsfml\StaticEntity.h"

/*
Vector containers holding all objects.
Seperate lists for interactalbe and static objects
*/
std::vector<sf::Vector2f> staticPositions;

StaticEntity firstObject(20, 40, 30, staticPositions);
StaticEntity secondObject(20, 90, 20, staticPositions);

bool isTruefalse = true;

int main(int argc, char* argv[]) {
	sf::RenderWindow App(sf::VideoMode(800, 600), "myproject");

	while (App.isOpen()) {
		sf::Event Event;

		while (App.pollEvent(Event)) {
			if (Event.type == sf::Event::Closed)
				App.close();			
		}
		
		
		App.draw(firstObject.getShape());
		App.draw(secondObject.getShape());
		App.display();
	}
}
